def Is_prime(num):
    if num < 2:
        return False
    limit = int(num**0.5)
    for i in range(2,limit+1):
        if num%i==0:
            return False
    return True

n=int(input())
if Is_prime(n):
    print(1)
else:
    print(0)
