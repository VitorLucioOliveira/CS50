import csv
import sys


def main():

    # Check for command-line usage
    argv = sys.argv
    if len(argv) != 3:
        print('Invalid number of Command-Line Argumentes')

    # Read database file into a variable
    database = []

    with open(argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(argv[2], 'r') as file:
        dna_seq = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    sub_seq = list(database[0].keys())[1:]

    result_list = {}

    for sub in sub_seq:
        result_list[sub] = longest_match(dna_seq, sub)

    # TODO: Check database for matching profiles
    for person in database:
        match = 0
        for sub in sub_seq:
            if int(person[sub]) == result_list[sub]:
                match += 1

        if match == len(sub_seq):
            print(person["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
