import cs50
from sys import argv, exit

# define main


def main():
    if len(argv) != 2:
        print("Usage: python roster.py House")
        exit()

    # open "students.db" for SQLite
    db = cs50.SQL("sqlite:///students.db")
    rosters = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ""?"" ORDER BY last, first", argv[1])

    # iterate over rosters
    for row in rosters:
        if row["middle"] == None:
            print(row['first'], " ", row['last'], ", born ", row['birth'], sep='')
        else:
            print(row['first'], " ", row['middle'], " ", row['last'], ", born ", row['birth'], sep='')


# call main
if __name__ == "__main__":
    main()