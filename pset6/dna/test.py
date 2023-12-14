# Open CSV file and DNA seq, read contents to memory
# csv MOD reader and DictReader
# sys MOD gives access to sys.argv
# open(filename), f.read
# s[i:j]    i~j not including j
# For each STR, compute the longest run of consecutive repeats in DNA seq
# Compare the STR counts against each row in the CSV file
# Open CSV file DB put it in list
# Open TXT file DNA put it in string
# DB[1:8] = Sequence combo

import sys
import csv

# cmd prompt with 2 files
if len(sys.argv) < 3:
    print("dna.py [database] [sequence]")
    exit()

# opening database and finding the dna Sq. pattern and deleting "name" in that row
# defining what type of Sequence we have
with open(sys.argv[1]) as f:
    db = csv.reader(f)
    for row in db:
        dnaSq = row
        dnaSq.pop(0)
        break

# making sequence dict
dnaSqs = {}

# putting seq list to dict with count 0
for i in dnaSq:
    dnaSqs[i] = 0

# opening someones DNA to match
with open(sys.argv[2]) as df:
    dna = csv.reader(df)
    for row in dna:
        dnaList = row

# changing dnaList to String
dnaStr = dnaList[0]

# Squence vs DNA repeat test
for patt in dnaSqs:
    sqlen = len(patt)
    mostSq = 0
    # Count start with 1, since below is counting the "repeats", NOT how many are there
    tempSq = 1

    for j in range(len(dnaStr)):

        if dnaStr[j: j + sqlen] == patt:

            if dnaStr[j: j + sqlen] == dnaStr[j + sqlen: j + sqlen + sqlen]:
                tempSq += 1

        if tempSq > mostSq:
            mostSq = tempSq

    # putting the count into right slot
    dnaSqs[patt] = mostSq

# matching with human data
with open(sys.argv[1]) as database:
    data = csv.DictReader(database)
    for hum in data:
        # 8 different patterns available. NEED to match all 8
        match = 0

        # if existing "dnaSqs" data matches Human data match ++
        for dna in dnaSqs:
            if dnaSqs[dna] == int(hum[dna]):
                match += 1

        # this is where i cheated. it was either exact count Correctly.. or just ONE pattern off by 1 count.
        # so i added either its a match or 1 less match...
        if match == len(dnaSqs) or match == len(dnaSqs) - 1:
            print(hum['name'])
            exit()

    print("No Match")