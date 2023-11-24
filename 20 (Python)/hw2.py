# Riley Fink
# 1895647

num = int(input("please enter the numerator: "))
remain = num
den = int(input("please enter the denominator: "))
div = int(0)
if num > 0:
    if den > 0:
        while remain >= den:
            remain -= den
            div += 1
        print(str(den) + " goes into " + str(num) + " this many times: " + str(div))
        print("the remainder is: " + str(remain))
    else:
        print("please input positive integers")
else:
    print("please input positive integers")