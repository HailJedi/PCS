x,d = map(int, input().split())
n = 1
ans = []
cnt = 0
for i in range(60,0,-1):
    if (x>>i) & 1:
        for j in range(1, i+1):
            ans.append(n)
        n += d
        cnt += 1
while cnt:
    ans.append(n)
    n += d
    cnt -= 1

if x & 1:
    ans.append(n)

print(len(ans))
for i in ans:
    print(i, end = ' ')
