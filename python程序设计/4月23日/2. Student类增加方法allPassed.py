class Student():
    def __init__(self):
        self.sno = 0
        self.name = ""
        self.mathScore = 0.0
        self.engScore = 0.0
        self.proScore = 0.0

    def average(self):
        return (self.mathScore + self.engScore + self.proScore) / 3

    def allPassed(self):
        if(self.mathScore >=60 and self.engScore >=60 and self.proScore >=60):
            return True
        else:
            return False




s = Student()
m, e, p = input().split()
s.mathScore = float(m)
s.engScore = float(e)
s.proScore = float(p)
if s.allPassed():
    print("All passed.")
else:
    print("Not all passed.")