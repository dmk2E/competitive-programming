'''アルゴリズムと工夫点(Axis-Parallel Rectangle/CPU: 637 ms Memory: 110628 KB  Length: 833 B)
全4辺上に1点以上点が存在するような長方形を全探索する．
最悪計算量は，O(N ^ 5) ≒ 10 ^ 8 となり間に合う．
'''
n, k = map(int, input().split())
xs = []
ys = []

for _ in range(n):
    a, b = map(int, input().split())
    xs.append(a);ys.append(b)

def judge(min_x: int, max_x: int, min_y: int, max_y: int) -> bool:
    global x, y, k
    cnt = 0
    for i in range(n):
        x = xs[i]
        y = ys[i]
        cnt += (min_x <= x and x <= max_x and min_y <= y and y <= max_y)
    return cnt >= k

ans = int(5e18)

for i in range(n):
    for j in range(0, i):
        min_x = min(xs[i], xs[j])
        max_x = max(xs[i], xs[j])
        for ii in range(n):
            for jj in range(0, ii):
                min_y = min(ys[ii], ys[jj])
                max_y = max(ys[ii], ys[jj])
                if judge(min_x, max_x, min_y, max_y):
                    ans = min(ans, (max_y - min_y) * (max_x - min_x))
print(ans)