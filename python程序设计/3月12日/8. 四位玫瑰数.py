def is_rose(str):
    num1 = int(str[0])
    num2 = int(str[1])
    num3 = int(str[2])
    num4 = int(str[3])
    if int(str) == num1**4 + num2**4 + num3**4 + num4**4:
        return True
    return False

for i in range (1000,10000):
    if(is_rose(str(i))):
        print(i)


