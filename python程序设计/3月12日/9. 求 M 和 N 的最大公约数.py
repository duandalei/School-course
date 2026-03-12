def gcd(a,b):
    if b==0:
        return a
    else:
        return gcd(b,a%b)

num1=int(input())
num2=int(input())
print(gcd(num1,num2))