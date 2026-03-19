def Is_prime(num):
    if num < 2:
        return False
    limit = int(num**0.5)
    for i in range(2, limit+1):
        if num % i == 0:
            return False
    return True

ls = eval(input())
#eval:把字符串当作“代码”执行,当输入:[1,2,3,4],eval() 会把这个字符串变成真正的列表
ls = [x for x in ls if not Is_prime(x)]

print(len(ls))