import csv
from sys import argv, exit

# define main


def main():
    # take command-line arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    # open the txtfile
    with open(argv[2]) as txtfile:
        sequences = str(txtfile.read())

    # open csvfile
    with open(argv[1], 'r') as csvfile:
        database = csv.DictReader(csvfile)
        # store fieldnames (STR names) to a list (headers)
        headers = database.fieldnames
        # create a dict which stores STR names as keys and STR counts as values
        STR_counts = {headers[x]: findSTR(headers[x], sequences) for x in range(1, len(headers))}
        matches = 0
        name = ""

        # the program is checking only the first STR
        for row in database:
            for STR in STR_counts:
                if STR_counts[STR] in row[STR]:
                    matches += 1
                else:
                    matches = 0
            if matches == len(headers) - 1:
                name = row['name']
                break

        if len(name) == 0:
            print("No match")
        else:
            print(name)


# define a function to find the maximum STR count of a particular STR
def findSTR(STR, sequence):
    current_count = 0
    all_counts = []
    size = len(STR)
    # for every character in the sequence
    # compare a particular substring with the given STR
    for char in range(len(sequence)):
        # if the substring is equal to the given STR increase count
        if sequence[char:char+size] == STR:
            current_count += 1
            # if the NEXT substring is NOT equal to the given STR we know that it is the end of the contiguous substring
            # add the count to the list containing all the STR counts in the sequence
            # prepare current_count for the next count
            if sequence[char+size:char+(2*size)] != STR:
                all_counts.append(current_count)
                current_count = 0
    if len(all_counts) == 0:
        print("No match")
        exit(0)
    # return the largest number in the list
    return str(max(all_counts))
    

# calling main function
if __name__ == "__main__":
    main()
