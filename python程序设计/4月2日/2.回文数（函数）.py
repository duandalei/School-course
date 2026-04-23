def huiwen1(num):
    ls=[]
    while num>0:
        ls.append(num%10)
        num //=10
    if ls[::] == ls[::-1]:
        return True
    else:
        return False

def huiwen2(a,b):
    for i in range(a,b+1):
        if huiwen1(i):
            print(i)


a,b = map(int, input().split())

huiwen2(a,b)