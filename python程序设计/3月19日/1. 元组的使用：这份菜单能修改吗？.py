menu_list = []
while True:
    try:
        food = input()
        menu_list.append(food)
    except:
        break

menu_tuple = tuple(menu_list)
print(menu_tuple)
print(max(menu_tuple)) #打印输出元组中首字母最大的元素