def isprime(n):
    n = int(n)
    if n < 2:
        return False
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True


num_str = input("")
num = eval(num_str)
reverse_num = eval(num_str[::-1])
if isprime(num) and isprime(reverse_num):
    print("yes")
else:
    print("no")