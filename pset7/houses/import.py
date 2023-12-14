import csv
import cs50
from sys import argv, exit

def main():
    # take command-line arguments
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        exit()

    # create empty "students.db"
    open("students.db", "w").close()
    # open "student.db" for SQLite
    db = cs50.SQL("sqlite:///students.db")

    # CREATE a table called "students" in "students.db"
    db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

    # open characters.csv given by the command-line argument
    with open(argv[1], "r") as file:
        reader = csv.DictReader(file)
        # iterate over the csv file
        for row in reader:
            # split the name form the "students.csv"
            name = row["name"].split()
            if len(name) == 2:
                name.append(name[1])
                name[1] = None
            else:
                pass

            # initialize the variables
            first = name[0]
            middle = name[1]
            last = name[2]
            house = row["house"]
            birth = row["birth"]

            # INSERT INTO "students" TABLE the VALUES from above variables
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)

# call main function
if __name__ == "__main__":
    main()