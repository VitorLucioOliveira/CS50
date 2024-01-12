#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;

} candidate;

#define MAX 9

candidate candidates[MAX];
int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // TESTANDO AS AGUAS
    if (argc < 2)
    {
        printf("Falta Candidatos");
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Muitos Candidatos");
        return 2;
    }

    // SETANDO OS CANDIDATOS
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // COMPUTANDO O VOTO
    int eleitores = get_int("Number of voters: ");

    for (int i = 0; i < eleitores; i++)
    {
        string name = get_string("Vote: ");
        if (!vote(name))
        {
            printf("Voto Invalido");
        }

    }

    print_winner();

    return 0;
}

bool vote(string name)
{
    bool resp = false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            resp = true;
        }
    }
    return resp;
}


void print_winner()
{
    int maximum_vote =0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maximum_vote)
        {
            maximum_vote = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maximum_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

}
