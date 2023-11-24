#Riley Fink
#1895647
# This is the final exam.

# I understand that getting help from a classmate or an external source would
# be a violation of academic integrity. So I did all of this work myself.
# signed: Riley Fink


### QUESTION ONE ###
import math
"""returns density of sphere given radius and mass"""
def ponder_orb_density(radius, mass):
    return mass / (4/3 * math.pi * (radius ** 3))


### QUESTION TWO ###
"""removes letters in letters_to_remove from message"""
def remove_letters(message, letters_to_remove):
    for i in letters_to_remove:
        message = message.replace(i, "")
    return message


### QUESTION THREE ###
"""returns list of ints where they could be found in the strings list, with the rest being 0s"""
def strings_to_ints(strings):
    newStrings = []
    for i in range(len(strings)):
        try:
            newStrings.append(int(strings[i]))
        except:
            newStrings.append(0)
    return newStrings


### QUESTION FOUR ###
"""counts number of instances of search terms in words list"""
def count_these_terms(words, search_terms):
    terms = {}
    for i in range(len(search_terms)):
        k = 0
        for j in range(len(words)):
            if words[j] == search_terms[i]:
                k += 1
        terms[search_terms[i]] = k
    return terms


### QUESTION FIVE ###
"""returns list of lines from file that contain given query"""
def select_lines_from_file(filename, query):
    file = open(filename, "r")
    lines = file.readlines()
    queryLines = []
    for i in range(len(lines)):
        if query in lines[i]:
            queryLines.append(lines[i])
    return queryLines


### QUESTION SIX ###
"""sums the highest 5 numbers given in list"""
def sum_highest_five(numbers):
    sum = 0
    if len(numbers) < 5:
        raise ValueError("ValueError exception thrown")
    for j in range(0,5):
        max = 0
        for i in range(len(numbers)):
            if numbers[i] > max:
                max = numbers[i]
        numbers.remove(max)
        sum += max
    return sum

### QUESTION SEVEN ###
""""""
class Friend:
    def __init__(self, name, height):
        self.name = name
        self.height = height
        self.favorite_foods = set()

    def add_favorite_food(self, food):
        self.favorite_foods.add(food)

    def number_of_favorite_foods(self):
        return len(self.favorite_foods)

    def __str__(self):
        foodlist = sorted(self.favorite_foods)
        foodstr = ", ".join(foodlist)
        return "[FRIEND name: {}, height: {}, favorite foods: {}]"\
            .format(self.name, self.height, foodstr)


class FriendsDB:
    def __init__(self):
        self.friends = []

    def add_friend(self, friend):
        self.friends.append(friend)

    def friends_who_love(self, food):
        out = sorted([friend.name for friend in self.friends
                      if food in friend.favorite_foods])
        return out

    def group_friends_by_food(self):
        food = []
        out = {}
        for i in range(len(self.friends)):
            line = str(self.friends[i])
            index = line.rfind(": ") +2
            for j in range(self.friends[i].number_of_favorite_foods()):
                index2 = line.find(",", index)
                if not food.__contains__(line[index:index2]):
                    food.append(line[index:index2])
                index = index2 +2
        for k in range(len(food)):
            out[food[k]] = self.friends_who_love(food[k])
        return out


### QUESTION EIGHT ###
"""returns sum of all nodes in binary tree"""
class BinaryTree:
    def __init__(self, value, leftchild, rightchild):
        self.value = value
        self.leftchild = leftchild
        self.rightchild = rightchild

def sum_binary_tree(tree):
    if(tree.leftchild == None):
        if(tree.rightchild == None):
            return tree.value
        return tree.value + sum_binary_tree(tree.rightchild)
    if(tree.rightchild == None):
        return tree.value + sum_binary_tree(tree.leftchild)
    return (tree.value + sum_binary_tree(tree.leftchild) + sum_binary_tree(tree.rightchild))

### QUESTION NINE ###
"""
running the code would throw an error since the Deer class doesn't have a method called speak(). 
to make it work as intended, you have to put the parent class Animal as an argument in the Deer class like:
class Deer(Animal):
...
after that change, it should work as expected, with the print statement firing:
hi my name is eleanor
"""

### QUESTION TEN ###
"""
The function should work as intended, but only if the list of words is already sorted alphabetically.
"""

