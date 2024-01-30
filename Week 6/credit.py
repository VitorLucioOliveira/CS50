from cs50 import get_int


def main():

    # Pegar o valor do cartão
    while True:
        card_number = get_int("Number: ")

        if card_number >= 0:
            break

    # Validar o cartão e printar sua marca
    if validate_card(card_number):
        card_brand(card_number)

    else:
        print("INVALID")


def validate_card(card_number):

    soma = 0

    # Loop que percorre o numero de algoritimos
    # Convertendo o int  para string: 1345 -> "1234"
    for i in range(len(str(card_number))):

        # Vamos alternar a cada digito
        if (i % 2 == 0):
            soma += card_number % 10  # Adicionamos o ultimo digito do cartão(sobra)
        else:
            digito = 2 * (card_number % 10)  # Dobramos o ultimo digito do cartão (sobra)
            soma += digito//10 + digito % 10  # Somamos o primeiro e ultimo digito do resultado: 12 -> 1+2

        # Tiramos o ultimo digito a cada iteração
        card_number //= 10

    # retorna true se a expressão "soma % 10 == 0" for verdadeira
    return soma % 10 == 0


def card_brand(card_number):

    size = len(str(card_number))
    primeiro_digito = int(str(card_number)[0])
    dois_digitos = int(str(card_number)[:2])

    if primeiro_digito == 4 and (size == 16 or size == 13):
        print("VISA")

    elif (dois_digitos == 34 or dois_digitos == 37) and size == 15:
        print("AMEX")

    elif (51 <= dois_digitos <= 55) and size == 16:
        print('MASTERCARD')

    else:
        print('INVALID')

    return


main()
