n, k = map(int, input().split())

A = [int(x) for x in input().split()]
T = [int(x) for x in input().split()]

dur = 0

for i in range(n):
    if T[i]:
        dur += A[i]
        A[i] = 0

s = sum(A[:k])
b = s
for i in range(k, n):
    s = s - A[i-k] + A[i]
    b = max(s, b)

print(dur+b)
