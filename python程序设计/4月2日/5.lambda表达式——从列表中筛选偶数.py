num_list = eval(input())
x = lambda ls: [x for x in ls if x % 2 == 0]
print(x(num_list))
