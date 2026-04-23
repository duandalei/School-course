def itob(n: int, b: int) -> str:
    digits = "0123456789abcdefghijklmnopqrstuvwxyz"

    if n == 0:
        return "0"

    sign = ""
    if n < 0:
        sign = "-"
        n = -n

    out = []
    while n > 0:
        out.append(digits[n % b])
        n //= b

    return sign + "".join(reversed(out))


def main():
    n, b = map(int, input().split())
    print(itob(n, b))


if __name__ == "__main__":
    main()
