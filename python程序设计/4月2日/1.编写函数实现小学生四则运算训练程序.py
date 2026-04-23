import random

data1=0
data2=0
op=""
opls=["+","-","*","//"]
correct_answer=0
correct_num=0
wrong_num=0

def give_question():
    global correct_answer
    data1 = random.randint(1, 100)
    data2 = random.randint(1, 100)
    op = random.choice(opls)
    print(f"{data1}{op}{data2}=",end="")
    if op == "+":
        correct_answer = data1 + data2
    elif op == "-":
        correct_answer = data1 - data2
    elif op == "*":
        correct_answer = data1 * data2
    else:
        correct_answer = data1 // data2


def judge():
    global correct_num, wrong_num
    huida = int(input())
    if (huida == correct_answer):
        correct_num = correct_num + 1
    else:
        wrong_num = wrong_num + 1
sd=input("请输入一个随机数种子：")
random.seed(sd)

for i in range(1,11):
    print("第{}题：".format(i))
    give_question()
    judge()

print("答对{}题，答错{}题".format(correct_num,wrong_num))

if correct_num>=8:
    print("你真棒！")
elif correct_num>6:
    print("还不错呢！")
else:
    print("还需要加油哦！")