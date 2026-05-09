'''アルゴリズムと工夫点(Distance Sum/CPU: 342 ms Memory: 126484 KB  Length: 459 B)
1次元に分割して考える．
すると，座標の最も小さい点を始点とした時の距離の総和を求め，
座標の昇順に始点をすらしながら総和を更新し，高速に解を計算することができる．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
'''
n = int(input())
xs = []
ys = []

for _ in range(n):
    x, y = map(int, input().split())
    xs.append(x);ys.append(y)

xs.sort();ys.sort()

sum_diff_x = 0
sum_diff_y = 0
for i in range(n):
    sum_diff_x += xs[i] - xs[0]
    sum_diff_y += ys[i] - ys[0]

ans = 0
for i in range(n - 1):
    ans += sum_diff_x + sum_diff_y
    sum_diff_x -= (n - i - 1) * (xs[i + 1] - xs[i])
    sum_diff_y -= (n - i - 1) * (ys[i + 1] - ys[i])

print(ans)
