from cs50 import get_string

text = get_string("Text: ")
letters = 0
words = 1
sentences = 0

for char in text:
    if char.isalpha():
        letters += 1
    if char.isspace():
        words += 1
    if char in [".", "!", "?"]:
        sentences += 1

l = letters * 100 / words
s = sentences * 100 / words

index = round(0.0588 * l - 0.296 * s - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")

