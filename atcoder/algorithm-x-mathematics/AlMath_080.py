'''アルゴリズムと工夫点(Difference Optimization 2/CPU: 1259 ms Memory: 184492 KB  Length: 603 B)
ダイクストラ法が解く．
xN の上界を求めることを考えると，整数x1~xN を頂点，Ciの値を重みとする辺を張った無向グラフ上で，
最短距離求めればよい．理由は，より厳しい条件が適用されること考えると,上界，つまり重みの総和は最小になるからである．
最悪計算量は，O((N + M) * log2(N + M)) < 10 ^ 7 となり高速．
'''
import heapq

n, m = map(int, input().split())
adj = [[] for _ in range(n)]

while m > 0:
    a, b, c = map(int, input().split())
    a -= 1;b -= 1
    adj[a].append((b, c))
    adj[b].append((a, c))
    m -= 1

pq = []
NIL = -1
max_x = [NIL for _ in range(n)]

heapq.heappush(pq, (0, 0))

while len(pq) > 0:
    cost, now_id = heapq.heappop(pq)
    if max_x[now_id] != NIL:
        continue
    max_x[now_id] = cost
    for nxt_id, nxt_cost in adj[now_id]:
        if max_x[nxt_id] == NIL:
            heapq.heappush(pq, (max_x[now_id] + nxt_cost, nxt_id))
print(max_x[n - 1])