email = input().strip()

if email.count('@') != 1: #)有且仅有一个'@'符号
    print("NO")
else:
    at_index = email.find('@')
    #'@'和'.'不能出现在字符串的首和尾
    if email[0] in ('@', '.') or email[-1] in ('@', '.'):
        print("NO")
    else:
        after_at = email[at_index + 1:]
        if '.' not in after_at: #'@'之后至少要有一个'.'
            print("NO")
        elif email[at_index + 1] == '.' or email[at_index - 1] == '.':#并且'@'不能和'.'直接相连
            print("NO")
        else:
            print("YES")