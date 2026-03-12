def caesar_cipher():
    # 获取输入并限制分割次数为 1，确保带空格的字符串不会被切断
    raw_input = input().split(' ', 1)

    if len(raw_input) < 2:
        return # 处理异常输入

    n = int(raw_input[0])
    text = raw_input[1]

    result = []

    for char in text:
        if 'A' <= char <= 'Z':
            # 处理大写字母：(当前索引 + 偏移量) % 26 + 起始位置
            new_char = chr((ord(char) - ord('A') + n) % 26 + ord('A'))
            result.append(new_char)
        elif 'a' <= char <= 'z':
            # 处理小写字母
            new_char = chr((ord(char) - ord('a') + n) % 26 + ord('a'))
            result.append(new_char)
        else:
            # 非字母字符（如空格）保持不变
            result.append(char)

    print("".join(result))

if __name__ == "__main__":
    caesar_cipher()