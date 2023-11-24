#Riley Fink
#1895647

class Friend:
    
    def __init__(self, name, height):
        self.name = name
        self.height = height
        self.foods = []

    def addFavFood(self, food):
        self.foods.append(food)

    def numofFavFoods(self):
        return len(self.foods)

    def returnFood(self, index):
        return self.foods[index]
  
    def __str__(self):
        list = []
        list.append("FRIEND name: "+ self.name)
        list.append("height: " + str(self.height))
        if len(self.foods) == 1:
            list.append("favorite foods: " + self.foods[0])
        elif len(self.foods) != 0:
            self.foods.sort()
            list.append("favorite foods: " + self.foods[0])
            for i in range(len(self.foods) - 1):
                list.append(self.foods[i+1])
        
        s = str(list)
        return s
            
class FriendsDB:
    
    def __init__(self):
        self.friends = []
    
    def addFriend(self, friend):
        self.friends.append(friend)

    def friendsWhoLove(self, food):
        tempFriends = []
        for i in range(len(self.friends)):
            num = self.friends[i].numofFavFoods()
            for j in range(num):
                if self.friends[i].returnFood(j) == food:
                    tempFriends.append(self.friends[i].name)
        return tempFriends
    
    def save(self, filename):
        file = open(filename, "w")
        for i in range(len(self.friends)):
            file.write(self.friends[i].name + "     " + str(self.friends[i].height) + "\t")
            for j in range(self.friends[i].numofFavFoods()):
                file.write(self.friends[i].returnFood(j) + "     ")
            file.write("\n")


def loadFriendsDB(filename):
    file = open(filename, "r")
    lines = file.readlines()
    db = FriendsDB()
    for i in range(len(lines)):
        temp = lines[i].split()
        globals()['friend%i' % i] = Friend(temp[0], temp[1])
        for j in range(len(temp)-2):
            globals()['friend%i' % i].addFavFood(temp[j+2])
        db.addFriend(globals()['friend%i' % i])
    return db