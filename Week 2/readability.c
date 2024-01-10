#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int contaLetras(string texto);
int contaPalavra(string texto);
int contaFrase(string texto);

int main(void)
{
    string texto = get_string("Text: ");

    float L = ((float) contaLetras(texto) / contaPalavra(texto)) * 100;

    float S = ((float) contaFrase(texto) / contaPalavra(texto)) * 100;

    float calculo = (0.0588 * L) - (0.296 * S) - 15.8;
    int index = round(calculo);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int contaLetras(string texto)
{
    int tam = strlen(texto);
    int letras = 0;

    for (int i = 0; i < tam; i++)
    {
        if ((texto[i] >= 'a' && texto[i] <= 'z') || (texto[i] >= 'A' && texto[i] <= 'Z')) // Verifica se o caractere é uma letra
        {
            letras++;
        }
    }

    return letras;
}

int contaPalavra(string texto)
{
    int tam = strlen(texto);
    int palavra = 1;

    for (int i = 0; i < tam; i++)
    {
        if (texto[i] == ' ')
        {
            palavra++;
        }
    }

    return palavra;
}

int contaFrase(string texto)
{
    int tam = strlen(texto);
    int frases = 0;

    for (int i = 0; i < tam; i++)
    {
        if (texto[i] == '?' || texto[i] == '.' || texto[i] == '!') // Verifica se o caractere é uma pontuação
        {

            frases++;
        }
    }

    return frases;
}
