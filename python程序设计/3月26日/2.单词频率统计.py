def count_word_frequency(text):
    # 1. 忽略大小写：统一转为小写
    text = text.lower()

    # 2. 忽略标点符号：使用 replace 方法清洗指定的标点
    for char in ",.!":
        text = text.replace(char, "")

    # 3. 将字符串分割成单词列表（默认按空格分割）
    words = text.split()

    # 4. 统计频率
    word_counts = {}
    for word in words:
        # 如果单词已在字典中，计数+1；不在则设为1
        word_counts[word] = word_counts.get(word, 0) + 1

    return word_counts


sample_text = input()
result = count_word_frequency(sample_text)
print(result)