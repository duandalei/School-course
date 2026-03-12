a=1
b=1
for i in range(1,21):
    print(a,end="  ")
    a,b=b,a+b
    if i%5==0:
        print()
