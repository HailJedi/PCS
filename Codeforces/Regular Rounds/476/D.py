w, l = map(int, input().split())
a = list(map(int, input().split()))

s = sum(a[:l])
r = s

for i in range(l, w-1):
    s += a[i]
    s -= a[i-l]
    r = min(s, r)

print(r)
