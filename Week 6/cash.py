from decimal import Decimal


def main():
    while True:
        try:
            cash = float(input("Change: "))

            if cash > 0:
                break
        except ValueError:
            pass

    coins = change(cash)
    print(coins)


def change(cash):
    quarters = dimes = nickels = pennies = 0
    cash = Decimal(str(cash))

    while cash >= Decimal('0.25'):
        quarters += 1
        cash = cash - Decimal('0.25')

    while cash >= Decimal('0.10'):
        dimes += 1
        cash -= Decimal('0.10')

    while cash >= Decimal('0.05'):
        nickels += 1
        cash -= Decimal('0.05')

    while cash >= Decimal('0.01'):
        pennies += 1
        cash -= Decimal('0.01')

    return (quarters + dimes + nickels + pennies)


main()
