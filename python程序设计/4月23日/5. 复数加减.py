s1 = input().strip()
s2 = input().strip()

# 解析复数 "a+bi"
def parse(s):
    a, bi = s.split('+')
    b = bi[:-1]  # 去掉末尾的 'i'
    return int(a), int(b)

a1, b1 = parse(s1)
a2, b2 = parse(s2)

# 加法
add_a = a1 + a2
add_b = b1 + b2

# 减法
sub_a = a1 - a2
sub_b = b1 - b2

# 格式化输出
def fmt(a, b):
    if b >= 0:
        return f"{a}+{b}i"
    else:
        return f"{a}{b}i"  # b自带负号，避免写成 -1+-1i

print(fmt(add_a, add_b))
print(fmt(sub_a, sub_b))



