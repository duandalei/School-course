import math

class Point:
    def __init__(self, x1, y1, z1):
        self.x1 = x1
        self.y1 = y1
        self.z1 = z1
    def dist_from(self, p2):
        dx = p2.x1 - self.x1
        dy = p2.y1 - self.y1
        dz = p2.z1 - self.z1
        return math.sqrt(dx * dx + dy * dy + dz * dz)


x1, y1, z1 = input().split()
x1 = float(x1)
y1 = float(y1)
z1 = float(z1)
p1 = Point(x1, y1, z1)
x2, y2, z2 = input().split()
x2 = float(x2)
y2 = float(y2)
z2 = float(z2)
p2 = Point(x2, y2, z2)
print("%.2f"%p1.dist_from(p2))