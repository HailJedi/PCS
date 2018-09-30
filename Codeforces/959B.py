I = lambda: input().split()
R = lambda: list(map(int, I()))
n, k, m = R()
w = dict(zip(I(), range(n)))
a = R()
for _ in [0]*k:
    x = R()[1:]
    c = min(a[i-1] for i in x)
    for i in x:
        a[i-1] = c
print(sum(a[w[x]] for x in I()))
