#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // altura
    int altura;
    do
    {
        altura = get_int("Height: ");
    }
    while (altura < 1 || altura > 8);

    for (int i = 0; i < altura; i++)
    {
        // printar os espaços iniciais
        for (int j = 0; j < altura - 1 - i; j++)
        {
            printf(" ");
        }

        // printar os # iniciais
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // printar o gap
        printf("  ");

        // printar os # finais
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // desce a linha
        printf("\n");
    }
}
