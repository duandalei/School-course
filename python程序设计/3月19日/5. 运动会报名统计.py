registration_data = [
    ["王平", "男", 1, 1, 0, 0],
    ["李丽", "女", 0, 1, 0, 1],
    ["陈小梅", "女", 0, 0, 1, 0],
    ["孙洪涛", "男", 0, 1, 1, 1],
    ["方亮", "男", 1, 0, 1, 0]
]

# 项目名称列表，方便后续输出
event_names = ["100m", "3000m", "跳远", "跳高"]


# 1. 求报名项目超过两项（含两项）的学生人数
count_two_plus = 0
for student in registration_data:
    events_count = sum(student[2:])
    if events_count >= 2:
        count_two_plus += 1
print(f"{count_two_plus}")

#2. 女生的报名情况
for student in registration_data:
    if student[1] == "女":
        name = student[0]
        print(name,end=' ')
        for i in range(2, 6):
            if student[i] == 1:
                # event_names 的索引需要对应减去 2
                print(event_names[i-2],end=' ')
        print()
#3. 报名3000m的学生姓名和性别
for student in registration_data:
    if student[3] == 1:
        print(f"{student[0]} {student[1]}")