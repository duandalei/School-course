def judge(n):
    if(n <= 1):
        return 0
    ans = 0
    for i in range(1, n):
        if(n % i == 0):
            ans += i
    if ans == n:
        return True
    else:
        return False


line = input()
temp = line.split(' ')
start = int(temp[0])
end = int(temp[1])
has = 0
for i in range(start, end + 1):
    if judge(i):
        has = 1
        print(i, end=' ')
if has == 0:
    print("No Answer")
