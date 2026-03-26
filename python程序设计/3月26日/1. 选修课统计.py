# 1. 定义选修各门课的学生名单（使用集合，方便进行去重和运算）
course1 = {"李雷", "张玉", "王晓刚", "陈红静", "方向", "司马清"}
course2 = {"施然", "李芳芳", "刘潇", "方向", "孙一航", "黄煌"}
course3 = {"陈红静", "方向", "刘培良", "张玉", "施小冉", "司马清"}

total_students_count = 25

# 2. 将所有选课名单合并，并统计每个学生出现的次数
# 我们可以把所有名单放在一个列表中
all_selections = list(course1) + list(course2) + list(course3)

# 3. 使用字典统计每位同学选了几门课
selection_counts = {}
for name in all_selections:
    selection_counts[name] = selection_counts.get(name, 0) + 1

# 4. 计算各项指标
# 选了课的总人数（去重后的学生集合）
selected_students = set(all_selections)
num_no_course = total_students_count - len(selected_students)

# 统计选了1门、2门、3门的人数
num_1_course = 0
num_2_courses = 0
num_3_courses = 0

for count in selection_counts.values():
    if count == 1:
        num_1_course += 1
    elif count == 2:
        num_2_courses += 1
    elif count == 3:
        num_3_courses += 1

# 5. 格式化输出
print("这个班有{}位学生没有选课，有{}位学生同时选修了2门课，有{}位同学同时选修了3门课，有{}位同学只选修了1门课".format(
    num_no_course, num_2_courses, num_3_courses, num_1_course
))