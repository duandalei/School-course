def sum_proper_divisors(x: int) -> int:
    """返回 x 的真因子和(包含1,不包含x本身)。"""
    if x <= 1:
        return 0

    total = 1
    d = 2
    while d * d <= x:
        if x % d == 0:
            total += d
            other = x // d
            if other != d:
                total += other
        d += 1
    return total


def main():
    n = int(input().strip())

    # 预计算 1..n 的真因子和，便于后续快速判断亲密数
    div_sum = [0] * (n + 1)
    for i in range(1, n + 1):
        div_sum[i] = sum_proper_divisors(i)

    for a in range(2, n + 1):
        b = div_sum[a]
        if b > a and b <= n and div_sum[b] == a:
            print(a, b)


if __name__ == "__main__":
    main()
