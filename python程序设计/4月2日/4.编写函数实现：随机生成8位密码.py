import random


def get_password() -> str:
    chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    return "".join(random.sample(chars, 8))


n = eval(input())
random.seed(n)
print(get_password())
