for i in range(100):
    ans = 0
    n = i
    for i in range(40):
        k = 1 << i
        ans += (n+k) // (k*2) * k
    print(ans, end = ' ')
