r = lambda: map(int, input().split())
h, m = r()
H, D, C, N = r()
H += N - 1
print( min( H // N * C, (H + max(0, 1200 - h * 60 - m) * D) // N * C * .8))
