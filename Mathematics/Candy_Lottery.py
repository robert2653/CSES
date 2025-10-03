from math import pow
from decimal import * # 無誤差浮點數

[n, k] = map(int, input().split())
ans = Decimal()

def power(a: Decimal, b: int):
    res = Decimal(1)
    while b:
        if b & 1:
            res *= a
        a *= a
        b >>= 1
    return res

for i in range(1, k + 1):
    ans += Decimal(i) * (power(Decimal(i) / k, n) - power(Decimal(i - 1) / k, n))

print(format(round(ans, 6), ".6f"))