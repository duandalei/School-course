class Rect():
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def area(self):
        return (self.x*self.y)



x = float(input())
y = float(input())
r1 = Rect(x, y)
print(r1.area())