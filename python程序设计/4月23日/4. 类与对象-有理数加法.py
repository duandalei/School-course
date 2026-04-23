from fractions import Fraction

a,b=input().split()
a = Fraction(a)
b = Fraction(b)
total = Fraction(0, 1)

total=total+a+b

if(total.denominator==0):
    print(total.numerator)
else:
    print(f"{total.numerator}/{total.denominator}")
