target=100
while True:
    num = int(input())
    if num==target:
        print("you win")
        break
    elif num<target:
        print("less than expected")
    else:
        print("larger than expected")
