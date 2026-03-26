fruit = ["苹果","梨子","菠萝","黄瓜","香蕉"]
vegetable = {"土豆","萝卜","茄子","白菜"}

#********* Begin *********#
#第一步 请将列表fruit转换为一个集合
fruit = set(fruit)

#第二步 将集合fruit中的“黄瓜”去掉
fruit.discard("黄瓜")

#第三步 使用"in"判断“黄瓜”是否在fruit中，将判断结果打印输出
print("黄瓜" in fruit)

#第四步 创建空集合food，输出集合food的长度
food = set()
print(len(food))

#第五步 将fruit和vegetable通过集合运算“并集”合并到food并输出此时food的长度
food = fruit | vegetable
print(len(food))

#********* End *********#
