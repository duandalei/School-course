cipher = input().strip()

plain = []
for ch in cipher:
    if 'A' <= ch <= 'Z':
        # 大写字母镜像
        plain.append(chr(ord('A') + ord('Z') - ord(ch)))
    elif 'a' <= ch <= 'z':
        # 小写字母镜像
        plain.append(chr(ord('a') + ord('z') - ord(ch)))
    else:
        # 非字母不变
        plain.append(ch)

plain_text = ''.join(plain)

print(cipher)
print()
print(plain_text)