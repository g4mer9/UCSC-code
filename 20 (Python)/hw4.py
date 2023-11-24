# Riley Fink
# 1895647

def integerDivision(x, y):
    remain = x
    div = int(0)
    if x > 0:
        if y > 0:
            while remain >= den:
                remain -= den
                div += 1
    return div

def updateNamesInList(names, oldname, newname):
    countMax = len(names) - 1
    count = 0
    while count <= countMax:
        if names[count] == oldname:
            names[count] = newname
        count += 1
    return names

def formLetter(x):
    template = "Dear {},\nYour appointment is at {}.\nThanks very much.\n-- bimmy"
    y = []
    tempString = template
    for i in range(0, len(x)):
        name = x[i].get("name")
        time = x[i].get("time")
        y.append(tempString.format(name, time))
        tempString = template
    return y

def makeWordBackwards(x):
    y = ""
    for i in range(1, len(x)+1):
        y+= x[-i]
    return y

def makeEachWordBackwards(x):
    y = ""
    wordEnd = 0
    wordBeg = 0
    k = 1
    for i in range(0, len(x)):
        if x[i] == " " or i == len(x) - 1:
            wordEnd = i
            if wordEnd == len(x) - 1:
                for j in range(wordBeg + 1, wordEnd + 2):
                    y += x[wordEnd - k+1]
                    k += 1
            else:
                for j in range(wordBeg+1, wordEnd+1):
                    y += x[wordEnd-k]
                    k += 1
            k = 1
            wordBeg = i + 1
            if wordEnd != len(x) - 1:
                y += " "
    return y