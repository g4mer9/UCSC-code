# Riley Fink
# 1895647

import math

def sphereVolume(x):
    x = float(((4/3) * math.pi * x ** 3))
    return x

def countNumbersGreaterThanFive(x):
    countMax = len(x) - 1
    count = 0
    y = 0
    while count <= countMax:
        if x[count] > 5:
            y += 1
        count += 1
    return y

def squareLargerNumber(x, y):
    if x > y:
        sqr = x ** 2
    else:
        sqr = y **2
    return sqr

def findBimmyOrJammy(names):
    countMax = len(names) - 1
    count = 0
    while count <= countMax:
        if names[count] == "bimmy":
            return "bimmy"
        if names[count] == "jammy":
            return "jammy"
        count += 1

def pluralizeEnglishWord(word):
    if word == "mouse":
        return "mice"
    elif word == "deer":
        return "deer"
    elif word == "person":
        return "people"
    elif word == "ox":
        return "oxen"
    elif word.endswith("x") or word.endswith("s") or word.endswith("sh") or word.endswith("ch") or word.endswith("z") or word.endswith("o"):
        return word + "es"
    else:
        return word + "s"