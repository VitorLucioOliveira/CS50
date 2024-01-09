#include <cs50.h>
#include <stdio.h>
#include <math.h>

int other_digit(long card);
int duplicaPica(int last_digit);
int contador(long card);
bool isAMEX(long card, int contador);
bool isMASTER(long card, int contador);
bool isVISA(long card, int contador);

int main(void)
{
    // variaveis
    long card = get_long("Number: ");
    int luth = other_digit(card);
    int c = contador(card);

    // validações
    if (luth % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (isAMEX(card, c))
    {

        printf("AMEX\n");
    }
    else if (isMASTER(card, c))
    {
        printf("MASTERCARD\n");
    }
    else if (isVISA(card, c))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int other_digit(long card)
{
    int soma = 0;

    bool alternado = false;

    while (card > 0)
    {
        if (alternado)
        {

            int last_digit = card % 10; // ultimo digito (sobra)
            int num = duplicaPica(last_digit);
            soma = num + soma;
        }
        else
        {
            int last_digit = card % 10;
            soma = last_digit + soma;
        }
        alternado = !alternado; // trocamos o valor de alternado para seu oposto
        card /= 10;             // tiramos o ultimo digito
    }

    return soma;
}

int duplicaPica(int last_digit)
{
    int multi = last_digit * 2;
    int soma = 0;

    while (multi > 0)
    {
        int las_digit_multi = multi % 10; // ultimo digito (sobra)
        soma = las_digit_multi + soma;
        multi /= 10; // tiramos o ultimo digito
    }
    return soma;
}

int contador(long card)
{
    int soma = 0;

    while (card > 0)
    {
        soma += 1;
        card /= 10;
    }

    return soma;
}

bool isAMEX(long card, int contador)
{
    bool resp = false;
    int dois = card / pow(10, 13); // isso pega os primeiros 2 digitos de um numero com 15 digitos

    if ((dois == 34 || dois == 37) && contador == 15)
    {
        resp = true;
    }

    return resp;
}

bool isMASTER(long card, int contador)
{
    bool resp = false;
    int dois = card / pow(10, 14); // isso pega os primeiros 2 digitos de um numero com 15 digitos

    if ((dois > 50 && dois < 56) && contador == 16)
    {
        resp = true;
    }

    return resp;
}

bool isVISA(long card, int contador)
{
    bool resp = false;
    if (contador == 13)
    {
        int um = card / pow(10, 12); // isso pega os primeiros 2 digitos de um numero com 15 digitos

        if (um == 4)
        {
            resp = true;
        }
    }
    else if (contador == 16)
    {
        int um = card / pow(10, 15); // isso pega os primeiros 2 digitos de um numero com 15 digitos

        if (um == 4)
        {
            resp = true;
        }
    }

    return resp;
}
