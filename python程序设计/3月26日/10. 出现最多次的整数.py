n=int(input())

ls=list(map(int,input().split()))

counter={}
for num in ls:
    counter[num] = counter.get(num,0)+1


max_cnt = max(counter.values())

for num in sorted(counter):
    if counter[num] == max_cnt:
        print(num, max_cnt)