from cs50 import get_string
import sys
from sys import argv


def main():
    """
        Takes a message and then censors out words according to a linked dictionary
    """
    # wrong number of command line args.
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    dict_ban = sys.argv[1]

    # open the censor dictionary
    file = open(dict_ban, "r")
    # comprehension from stack overflow
    banned = set(line.strip()for line in file)

    # get user input, message
    message = get_string("What message would you like to censor?\n")

    # format message
    new_message = message.split()

    # iterate over message list
    for word in new_message:
        # check if word is banned
        if word.lower() in banned:
            # get the length of each word
            length = len(word)
            # print censored word
            print("*" * length, end="")
            print(" ", end="")
        else:
            # print regular word
            print(word, end="")
            print(" ", end="")

    # print new line at the end
    print()


# run main when the program starts
if __name__ == "__main__":
    main()