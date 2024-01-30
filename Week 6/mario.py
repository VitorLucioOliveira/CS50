

while True:

    try:
        height = int(input("Height: "))

        if height <= 8 and height > 0:
            break
    except ValueError:
        pass


for i in range(height):

    # Print first column
    print(" " * (height-i-1), end="")
    print("#" * (i+1), end="")

    # Print gap
    print("  ", end="")

    # Print second column
    print("#" * (i+1))
