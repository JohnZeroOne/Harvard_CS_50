# calculates coins for given amount of change
from cs50 import get_float

# get user input
while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break
# convert dollars to cents
cents = int(dollars*100)
# keep track of coins/change needed
num_coins = 0
# give greedy coins until we have paid all change
while cents > 0:
    if cents // 25 > 0:
        num_coins += 1
        cents -= 25
    elif cents // 10 > 0:
        num_coins += 1
        cents -= 10
    elif cents // 5 > 0:
        num_coins += 1
        cents -= 5
    elif cents // 1 > 0:
        num_coins += 1
        cents -= 1
# return the total number of coins needed
print(num_coins, "\n")