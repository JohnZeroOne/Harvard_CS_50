import sys
from sys import argv, exit
from cs50 import get_string
import string

# exit if we weren't given 1 command line argument
if len(sys.argv) != 2:
    print("caesar usage: caesar.py 1")
    sys.exit("1")

# cypher shift from command line
k = int(sys.argv[1])

# get plaintext from user
p = get_string("plaintext: ")

# store cyphertext
c = []

# start return message
print("ciphertext: ", end="")

# encipher plaintext with cypher shift
for char in p:
    # received a letter
    if char.isalpha():
        # uppercase letter
        if char.isupper():
            num = ord(char)
            num -= 65
            num += k
            num = num % 26
            num += 65
            let = chr(num)
            print(let, end="")
        # lowercase letter
        elif char.islower():
            num = ord(char)
            num -= 97
            num += k
            num = num % 26
            num += 97
            let = chr(num)
            print(let, end="")
    # received anything but letter
    else:
        print(char, end="")

# new line for formatting
print()