for i in range(1,10):
    for j in range(1,i+1):
        print(f"{i}*{j}={i*j}",end=" ")
    print()

#table = [[f"{j}×{i}={i*j}" for j in range(1, i+1)] for i in range(1, 10)]
