#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculo(string palavra);

// valores de cada litre da alfabeto
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{

    // strings ddos players
    string players[2];

    for (int i = 0; i < 2; i++)
    {
        players[i] = get_string("Player %i: ", i + 1);
    }

    // calculo dos pontos
    int p1 = calculo(players[0]);
    int p2 = calculo(players[1]);

    // comparação
    if (p1 > p2)
    {
        printf("Player 1 wins!");
    }
    else if (p1 < p2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int calculo(string palavra)
{
    int pontos = 0;

    // unifica as maiusculas e minusculas
    int tam = strlen(palavra);
    for(int i = 0; i< tam; i++)
    {
        palavra[i]= tolower(palavra[i]);
        pontos += POINTS[palavra[i] - 'a'];
    }

    //calculo de pontos

    return pontos;
}
