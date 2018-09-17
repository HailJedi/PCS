read = lambda: map(int, input().split())
n, m = read()
a = [0] * n
for c in read():
    a[c-1]+=1
print(min(a))
