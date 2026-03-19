N = int(input())
size = 2 * N - 1

for i in range(size):
    for j in range(size):
        value = min(i, j, size - 1 - i, size - 1 - j) + 1
        print(value, end='')
    print()