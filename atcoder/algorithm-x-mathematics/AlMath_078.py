'''アルゴリズムと工夫点(Difference Optimization 1/CPU: 286 ms Memory: 125436 KB  Length: 553 B)
最適化問題は，値の上界を考える．
複数の条件がある場合は，1つずつ順番に条件を適用し，上界を計算していく．＠
今回の問題の場合，0歳の人1から順に，条件を適用していき，全員の最大の歳を求めていく．
より厳しい条件が適用されるため，人を頂点，歳の差の関係を辺で表した無向グラフにおいて，
人1を始点とした最短距離（辺の重さ1とし）が，人それぞれの最大の歳となる．
最悪計算量は，O(N + M) < 10 ^ 7 となり高速．
'''
from collections import deque

n, m = map(int, input().split())

adj = [[] for _ in range(n)]
while m > 0:
    a, b = map(int, input().split())
    a -= 1;b -= 1
    adj[a].append(b)
    adj[b].append(a)
    m -= 1

INF = n + 1
MAX_AGE = 120

dist = [INF for _ in range(n)]

deq = deque()
dist[0] = 0
deq.append(0)
while len(deq) > 0:
    now = deq.popleft()
    for nxt in adj[now]:
        if dist[nxt] == INF:
            dist[nxt] = dist[now] + 1
            deq.append(nxt)

for ans in dist:
    print(min(ans, MAX_AGE))