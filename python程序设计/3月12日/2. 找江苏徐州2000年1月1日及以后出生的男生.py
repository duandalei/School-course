import sys
ID = input().strip()

if len(ID) != 18:
    print("no")
    sys.exit()

if not ((ID[0:17].isdigit() and ID[17].upper()=='X') or ID.isdigit()):
    print("no")
    sys.exit()

city=ID[0:4]
gender=int(ID[16])
birsday = ID[6:14]

if  city=="3203" and birsday >= "20000101" and gender % 2!=0 :
    print("yes")
else:
    print("no")
