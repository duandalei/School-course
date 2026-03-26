# 1. 获取输入并转换为集合
# 输入格式通常为 "1,3,4..."，我们需要先按逗号分割，再转为 int，最后转为 set
input1 = input()
input2 = input()

# 使用列表推导式快速转换
hd1 = set(int(x) for x in input1.split(','))
hd2 = set(int(x) for x in input2.split(','))

# 2. 进行集合运算
# (1) 同时参加两项活动：使用交集 &
both_activities = hd1 & hd2

# (2) 只参加活动1：使用差集 - (在hd1中但不在hd2中)
only_hd1 = hd1 - hd2

# (3) 只参加活动2：使用差集 - (在hd2中但不在hd1中)
only_hd2 = hd2 - hd1

# 3. 按要求格式输出结果
print("两项活动都参加", both_activities)
print("只参加活动1", only_hd1)
print("只参加活动2", only_hd2)