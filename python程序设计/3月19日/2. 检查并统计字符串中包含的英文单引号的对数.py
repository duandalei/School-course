st = input()
pair=0
for s in st:
    if s=="'":
        pair+=1

if pair == 0:
    pro = "None of a pair"
elif pair % 2 == 0:
    cnt = pair//2
    pro =f"There are {cnt} pairs"
else:
    cnt = pair // 2
    pro =f"There are {cnt} pairs with a half one"

print(pro)