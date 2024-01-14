#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int valor_vitoria(pair pair);
void lock_pairs(void);
bool has_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Inicializando array de candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Inicializando array de locked pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Percorre o array em busca do nome do candidato
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // O index rank(Ordem do input), armazena candidato escolhido (representado pela ordem numerica deles, 1~~n )
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int li = 0; li < candidate_count; li++)
    {
        for (int col = li + 1; col < candidate_count; col++)
        {
            /*
            Primeira interação do Loop:

                O rank[li] representa o primeiro candidato escolhido pelo votador;
                O rank[col], que é li+1, representa o segundo candidato do votador;

                Sendo assim, ela vai na posição de comparação delas e soma 1;
            Segunda interação do Loop:

                O rank[li]  representa o primeiro candidato escolhido pelo votador;
                O rank[col], que é li+1, agora representa o terceiro candidato do votador;

                Sendo assim, ela vai na posição de comparação delas e soma 1;
            Saida e volta do Loop:

                Ao sair do loop interno e ir pro loop externo, ela adiciona +1 ao li
                Ou seja, agora o rank[li] representa o segundo candidato do votador;
                E rank[col], que é li+1, agora representa o terceiro candidato do votador;

                Sendo assim, na comparação agora de qual voi preferido entre o segundo e terceiro
            */

            preferences[ranks[li]][ranks[col]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair new = {i, j};
                pairs[pair_count++] = new;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i <= pair_count; i++)
    {
        int maior_dif = valor_vitoria(pairs[i]); // Valor da posição
        int maior_index = i;                     // posição do maior index

        for (int j = i + 1; j <= pair_count; j++)
        {
            if (maior_dif < valor_vitoria(pairs[j]))
            {
                maior_dif = valor_vitoria(pairs[j]);
                maior_index = j;
            }
        }

        if (maior_index != i)
        {
            pair tmp = pairs[i];
            pairs[i] = pairs[maior_index];
            pairs[maior_index] = tmp;
        }
    }
}

// Returns the value of votes that the winner wins for
int valor_vitoria(pair pair)
{
    return preferences[pair.winner][pair.loser];
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {

        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Identify if the locek winner is in a cycle
bool has_cycle(int winner, int loser)
{
    // Verifica se o loser tambem ganha do winner,isso é um ciclo
    if (locked[loser][winner] == true)
    {
        return true;
    }

    // Percorre o array, procurando se o loser ganhou de alguem e se esse alguem foi o vencedor, isso é um ciclo
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && has_cycle(winner, i))
        {
            return true;
        }
    }

    return false;
}
// Print the winner of the election
void print_winner(void)
{
    // Loop que percorre todos os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        // Inicializa o candidato como vencedor, ate que se prove o contrario
        bool winner = true;

        // Loop que verifica se essa candidato perdeu pra alguem (Se ele perder significa que tem ciclo/erro)
        for (int j = 0; j < candidate_count; j++)
        {

            if (locked[j][i] == true)
            {
                winner = false;
                break;
            }
        }

        if (winner)
        {
            printf("%s\n", candidates[i]);
            i = candidate_count;
        }
    }
}
