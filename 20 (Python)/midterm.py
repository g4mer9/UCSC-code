# Riley Fink
#1895647
# This is the midterm exam.

# I understand that getting help from a classmate or an external source would
# be a violation of academic integrity. So I did all of this work myself.
# signed: Riley Fink

import math

### QUESTION ONE ###
# area =  (rt(3)/4) * a^2
def area_of_equilateral_triangle(a):
    return (math.sqrt(3) / 4) * a ** 2


### QUESTION TWO ###
#takes list of strings, returns count of fred and ted
def count_fred_and_ted(names):
    fredTedCount = 0
    for i in range(len(names)):
        if names[i] == "fred" or names[i] == "ted":
            fredTedCount += 1
    return  fredTedCount


### QUESTION THREE ###
#takes 3 nums, returns sum of greater two
def sum_of_greatest_two(a, b, c):
    temp = [a, b, c]
    greatest = max(temp)
    temp.remove(greatest)
    second = max(temp)
    return greatest + second

### QUESTION FOUR ###
#takes string of plural pet type, changes to singular and returns template with singular put in
def pet_shopping_list(pet_type):
    if pet_type == "mice":
        petName = "mouse"
    elif pet_type[len(pet_type) - 2:] == "es":
        petName = pet_type[:len(pet_type) - 2]
    elif pet_type[len(pet_type) - 1:] == "s":
        petName = pet_type[:len(pet_type) - 1]
    else:
        petName = pet_type
    template = [" food", " treats", " bed", " house"]
    new = []
    for i in range(len(template)):
        new.append(petName + template[i])
    return new

### QUESTION FIVE ###
#takes int balance and list of tuples of template ("name", price, "deposit/withdrawal") and returns new balance
def calculate_new_balance(start, transactions):
    for i in range(len(transactions)):
        if transactions[i][2] == "deposit":
            start += transactions[i][1]
        else:
            start -= transactions[i][1]
    return start

### QUESTION SIX ###
#takes num and returns list of all perfect squares up to n^2
def list_n_perfect_squares(n):
    nums = []
    for i in range(1, (n ** 2) +1):
        rt = math.sqrt(i)
        if int(rt) ** 2 == i:
            nums.append(i)
    return nums

### QUESTION SEVEN ###
#uses .isdigit to return true/false on username
def username_ends_with_digits(username):
    if username[len(username)-1:].isdigit():
        return True
    else:
        return False

### QUESTION EIGHT ###
#takes list of dicts and returns list of tuples with just names and addresses
def names_with_addresses(friends):
    new = []
    for i in range(len(friends)):
        new.append((friends[i].get("name"), friends[i].get("address")))
    return new

### QUESTION NINE ###
"""
[] is printed since it prints the wrong list. changing the last line to print(result) would make it work as intended.
"""

### QUESTION TEN ###
"""
Assuming the function doesn't have a return statement and that the "print(square_number(square_number(square_number(2))))" line is the same,
instead of just printing 256 like the first function, it would print 4 and then throw an error since the print call was moved inside the function and
square_number(2) returns nothing so the next nested call would fail.
"""
