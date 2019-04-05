import nltk.tokenize
import string
import re
from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # split each string into lines
    alist = a.splitlines()
    blist = b.splitlines()

    # convert to sets to remove duplicate lines
    a = set(alist)
    b = set(blist)
    c = set()

    # compute a list of lines in both a and b
    for item in a:
        if item in b:
            c.add(item)

    # return the list
    return c


def sentences(a, b):
    """Return sentences in both a and b"""

    # split each string into sentences (split them when there is punctuation)
    a = nltk.tokenize.sent_tokenize(a, language='english')
    b = nltk.tokenize.sent_tokenize(b, language='english')
    c = set()

    # calculate the list of sentences that appear in both A and B
    for sentence in a:
        if sentence in b:
            c.add(sentence)

    # return the list
    return c


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # get the length
    length_a = len(a)
    length_b = len(b)

    # store substrings without duplicates
    a_set = set()
    b_set = set()

    # get substrings
    for i in range(length_a - n + 1):
        a_set.add(a[i:(n+i)])
    for i in range(length_b - n + 1):
        b_set.add(b[i:(n+i)])

    # compute list of all substrings appearing in both A and B
    c = set()
    for substring in a_set:
        if substring in b_set:
            c.add(substring)

    # return list
    return c