'''アルゴリズムと工夫点(Number of Multiples 2/CPU: 3411 ms Memory: 182276 KB  Length: 661 B)
二次元累積和で解く．
最悪計算量は，O(H * W) < 10 ^ 7 となり高速．
'''

h, w = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(h)]

sum_a = [[0] * (w + 1) for _ in range(h + 1)]

for i in range(h):
    for j in range(w):
        sum_a[i + 1][j + 1] = sum_a[i][j + 1] + sum_a[i + 1][j] - sum_a[i][j] + a[i][j]

def calc(sy: int, sx: int, gy: int, gx: int) -> int:
    global sum_a
    return sum_a[gy + 1][gx + 1] - sum_a[gy + 1][sx] - sum_a[sy][gx + 1] + sum_a[sy][sx]

for i in range(h):
    j = 0
    while j < w - 1: 
        print(f"{calc(i, 0, i, w - 1) + calc(0, j, h - 1, j) - a[i][j]} ", end = "")
        j += 1
    print(calc(i, 0, i, w - 1) + calc(0, j, h - 1, j) - a[i][j])