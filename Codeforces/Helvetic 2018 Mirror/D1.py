m = int(input())
esc = [eval(input()) for i in range(m)]
d = {i: 0 for i in esc}
for i in esc:
    d[i] += 1
for i in esc:
    print(d[i], end = ' ')
