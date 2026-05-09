'''アルゴリズムと工夫点(Linear Programming/CPU: 117 ms Memory: 109540 KB  Length: 885 B)
2直線の交点を全列挙し，判定して解く．
線形計画法では，2直線交点のみが，x + y の値を最大にし得る．
よって交点を全列挙し，各点が条件を満たすか判定すればよい．
最悪計算量は，O(N ^ 3) ≒ 10 ^ 8 となり間に合う．
'''
def is_crossed(i: int, j: int) -> bool:
    global lines
    a1, b1, c1 = lines[i]
    a2, b2, c2 = lines[j]
    return a1 * b2 != b1 * a2

def get_cross_point(i: int, j: int) -> tuple[int, int]:
    global lines
    a1, b1, c1 = lines[i]
    a2, b2, c2 = lines[j]
    return ((c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1))

def judge(x: float, y: float) -> bool:
    global lines, EPS
    for i in range(n):
        a, b, c = lines[i]
        if a * x + b * y - c > EPS: 
            return False
    return True

EPS = 0.000000000001
n = int(input())
lines = [list(map(int, input().split())) for _ in range(n)]

ans = 0.0
for i in range(n):
    for j in range(0, i):
        if is_crossed(i, j):
            x, y = get_cross_point(i, j)
            if judge(x, y):
                ans = max(ans, x + y)
print(ans)