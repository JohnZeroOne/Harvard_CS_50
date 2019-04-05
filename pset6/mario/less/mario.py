# makes a Mario pyramid from user input
from cs50 import get_int

h = 0
# get user input
while h > 8 or h < 1:
    h = get_int("Height: ")
# print horizontal bricks
for i in range(h):
    print(" " * (h - (i + 1)) + "#" * (i + 1))