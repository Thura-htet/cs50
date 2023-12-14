from cs50 import get_float

while True:
    change = round(get_float("Change: ") * 100)
    if change >= 0:
        break

num = 0
coins = [25, 10, 5, 1]

for i in range(len(coins)):
    num += int(change / coins[i])
    change = change % coins[i]

print(f"{num}")

