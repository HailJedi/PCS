n, k, M, D = map(int, input().split())

ans = 0
for d in range(1, D+1):
    x = min(M, n // (k * (d - 1) + 1))
    if x == 0:
        continue
    rd = (n // x + k - 1) // k
    if rd != d:
        continue;
    ans = max(ans, x*d)
print(ans)
