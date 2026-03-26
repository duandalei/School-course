n=int(input())

ls=list(map(int,input().split()))

counter={}
for num in ls:
    counter[num] = counter.get(num,0)+1

for num, cnt in sorted(counter.items(), key=lambda x: (-x[1], x[0])):
    print(num, cnt)