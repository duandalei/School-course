from fractions import Fraction

# 读取输入
n = int(input())
nums = input().split()

total = Fraction(0, 1)

# 累加所有分数
for x in nums:
    total += Fraction(x)

# 求平均
avg = total / n

# 输出
if avg.denominator == 1:
    print(avg.numerator)
else:
    print(f"{avg.numerator}/{avg.denominator}")