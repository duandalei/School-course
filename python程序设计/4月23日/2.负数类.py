def add(a, b, c, d):
    return a + c, b + d

def sub(a, b, c, d):
    return a - c, b - d

def mul(a, b, c, d):
    return a * c - b * d, a * d + b * c



s1 = input().strip()
s2 = input().strip()


a, b = map(int, s1[1:-1].split(','))
c, d = map(int, s2[1:-1].split(','))

def format_complex(x, y):
    if y >= 0:
        return f"{x}+{y}i"
    else:
        return f"{x}{y}i"


z1 = f"({format_complex(a, b)})"
z2 = f"({format_complex(c, d)})"

ra, rb = add(a, b, c, d)
print(f"{z1}+{z2}={format_complex(ra, rb)}")

ra, rb = sub(a, b, c, d)
print(f"{z1}-{z2}={format_complex(ra, rb)}")

ra, rb = mul(a, b, c, d)
print(f"{z1}*{z2}={format_complex(ra, rb)}")