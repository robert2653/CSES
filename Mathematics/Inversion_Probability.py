from math import pow
from decimal import * # 無誤差浮點數
# print(getcontext())
setcontext(Context(prec=100))

n = int(input())
a = list(map(int, input().split()))
ans = Decimal()

for i in range(n):
    for j in range(i + 1, n):
        x = 1
        if a[i] <= a[j]:
            x = a[i] * (a[i] - 1) // 2
        else:
            x = (a[j] + 1) * a[j] // 2 + (a[i] - a[j] - 1) * a[j]
        ans += Decimal(x) / a[i] / a[j]
        
print(format(round(ans, 6), ".6f"))