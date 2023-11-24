#Riley Fink
#1895647

def saveFriendsdb(friends, filename):
    file = open(filename, "w")
    for i in range(len(friends)):
        file.write(friends[i].get("name") + "   " + str(friends[i].get("height")) + "\n")

def loadFriendsdb(filename):
    file = open(filename, "r")
    friendsdb = []
    while True:
        lineIndex = 0
        nextline = file.readline()
        if nextline == "":
            break
        else:
            for i in range(0, len(nextline)):
                if nextline[i] != " ":
                    lineIndex += 1
                elif nextline[i+1] == " ":
                    break
                else:
                    lineIndex +=1
            friendsdb.append({"name": nextline[:lineIndex], "height": nextline[lineIndex+3:lineIndex+6]})
    return friendsdb

def lookupFriendsHeights(friends, names):
    heightList = []
    for i in range(len(names)):
        foundName = True
        for j in range(len(friends)):
            if names[i] == friends[j].get("name"):
                heightList.append(friends[j].get("height"))
                foundName = True
                break
            else:
                foundName = False
        if foundName == False:
            heightList.append("None")
    return heightList

class Friend:
    foods = []
    def __init__(self, name, height):
        self.name = name
        self.height = height

    def addFavFood(self, food):
        self.foods.append(food)

    def numofFavFoods(self):
        return len(self.foods)

class GameEnemy:
    def __init__(self, name, x, y, hp):
        self.name = name
        self.x = x
        self.y = y
        self.hp = hp

    def healthBar(self):
        hpCount = ""
        for i in range(self.hp):
            hpCount += "*"
        print(self.name + ": " + hpCount)