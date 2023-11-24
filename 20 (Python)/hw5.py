#Riley Fink
#1895647

import math

def countPerfectSquares(nums):
    j = 0
    for i in nums:
        rt = math.sqrt(i)
        if int(rt) ** 2 == i:
            j+=1
    return j

def areAnagrams(x, y):
    xCut = ""
    yCut = ""
    for z in range(len(x)):
        if x[z] != " ":
            xCut += x[z].lower()
    xSort = sorted(xCut)
    for i in range(len(y)):
        if y[i] != " ":
            yCut += y[i].lower()
    ySort = sorted(yCut)
    if xSort == ySort:
        return True
    else:
        return False

#takes list of tuples name, year, dir, and returns list of tuples with dir
def findMoviesByDirector(movies, dir):
    newList = []
    for i in range(len(movies)):
        if movies[i][2] == dir:
            newList.append(movies[i])
    return newList

#takes list of dicts format "name": "bimmy", "height": 60 and returns dict with longest name
def findFriendWithLongestName(x):
    y = 0
    if len(x) != 0:
        for i in range(len(x)):
            if len(x[i].get("name")) >= len(x[y].get("name")):
                y = i
        return x[y]
    else:
        return []

#takes list of dicts and returns ordered list of dicts
def sortFriendsByNameLength(x):
    newList = []
    for i in range(len(x)):
        newList.append(findFriendWithLongestName(x))
        x.remove(findFriendWithLongestName(x))
    return newList