# 读入字典
data = eval(input())

# 输出表头（制表符分隔）
print("name\tChinese\tMath\tEnglish\tPython\tAverage")

# 姓名按升序
for name in sorted(data):
    chinese, math, english, python_score = data[name]
    avg = (chinese + math + english + python_score) / 4
    print(f"{name}\t{chinese}\t{math}\t{english}\t{python_score}\t{avg}")