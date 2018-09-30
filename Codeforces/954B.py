n = int(input())
a = input()
x = 0
for i in range(n//2, 1, -1):
    if a[0:i] == a[i:(i+i)]:
        x = i-1
        break
print(n-x)
