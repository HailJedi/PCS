s = input()
t = set(s)
l = len(t)
print(['No', 'Yes'][2 <= l <= 4 and l + sum(s.count(x) >= 2 for x in t) >= 4])
