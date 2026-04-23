def sieve(limit: int):
    """返回 0..limit 的素数布尔表。"""
    if limit < 2:
        return [False] * (limit + 1)
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    p = 2
    while p * p <= limit:
        if is_prime[p]:
            step = p
            start = p * p
            for x in range(start, limit + 1, step):
                is_prime[x] = False
        p += 1
    return is_prime


def main():
    n = int(input().strip())
    is_prime = sieve(n)

    for even in range(4, n + 1, 2):
        for p in range(2, even // 2 + 1):
            if is_prime[p] and is_prime[even - p]:
                print(f"{even}={p}+{even - p}")
                break


if __name__ == "__main__":
    main()
