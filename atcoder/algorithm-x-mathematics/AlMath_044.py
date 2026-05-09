'''アルゴリズムと工夫点(Shortest Path 1/CPU: 166 ms Memory: 101296 KB  Length: 576 B)
最短距離を求めるなら，BFSで行う．
実装ではキューが必要であり，今回はdequeを用いて実装した．
DFSやBFSなど，基本的に探索では同じ状態を生成しないように，状態毎に既に生成されたか否かのフラグを持たせる必要がある．
今回は，vis[i]=(頂点1から頂点iまでの最短距離) とし，初期値をINFとすることで，INFか否かで既に生成されたかを判定する．
また，BFSを極めたい人に向けて押さえておくべきBFSを以下にまとめておく．
-(応用)色んなBFSメモ--
・01-BFS
・多始点BFS
・拡張BFS
'''
from collections import deque
n,m=map(int,input().split())
adj=[[] for _ in range(0,n)]

while m>0:
    a,b=map(int,input().split())
    adj[a-1].append(b-1)
    adj[b-1].append(a-1)
    m-=1

INF=int(1e5)
vis=[INF for _ in range(0,n)]

def bfs(now:int):
    deq=deque()
    deq.append(now)
    vis[now]=0
    while len(deq)>0:
        now=deq.popleft()
        for nxt in adj[now]:
            if vis[nxt]==INF:
                vis[nxt]=vis[now]+1
                deq.append(nxt)

bfs(0)
for i in range(0,n):
    print(-1 if vis[i]==INF else vis[i])