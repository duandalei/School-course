def Is_prime(num):
    if num < 2:
        return False
    limit = int(num**0.5)
    for i in range(2,limit+1):
        if num%i==0:
            return False
    return True
ans=0

for n in range(1,101):
    if Is_prime(n):
        ans+=n

print(ans)



