def add(a, b, c, d):
    return a + c, b + d

def sub(a, b, c, d):
    return a - c, b - d

def mul(a, b, c, d):
    return a * c - b * d, a * d + b * c

def div(a, b, c, d):
    denominator = c**2 + d**2
    real = (a * c + b * d) / denominator
    imag = (b * c - a * d) / denominator
    return real, imag



data = input().split()
x = data[0]
a, b, c, d = map(float, data[1:])
res_a, res_b=0,0

if x == '+':
    res_a, res_b = add(a, b, c, d)
elif x == '-':
    res_a, res_b = sub(a, b, c, d)
elif x == '*':
    res_a, res_b = mul(a, b, c, d)
elif x == '/':
    res_a, res_b = div(a, b, c, d)


if res_b >= 0:
    print(f"{res_a:.2f}+{res_b:.2f}i")
else:
    print(f"{res_a:.2f}-{abs(res_b):.2f}i")