'''アルゴリズムと工夫点(Bipartite Graph/CPU: 370 ms Memory: 289532 KB  Length: 678 B)
二部グラフの条件は，「"連結成分毎"で，辺で結ばれた2頂点を異なる色で塗り分けられる」ことである．
DFSやBFSで実装可能．最悪計算量は，O(N+M)<10^6 となり十分高速．
※グラフの問題では常に，「そのグラフは連結か？」を意識しよう．
'''
import sys
sys.setrecursionlimit(10**6)

n,m=map(int,input().split())
adj=[[] for _ in range(0,n)]

while m>0:
    a,b=map(int,input().split())
    adj[a-1].append(b-1)
    adj[b-1].append(a-1)
    m-=1

NIL=-1
RED=0
BLUE=1
color=[NIL for _ in range(0,n)]

def dfs(now:int,c:int)->bool:
    color[now]=c
    for nxt in adj[now]:
        if color[nxt]==NIL:
            if dfs(nxt,(BLUE if c==RED else RED))==False:
                return False
        elif color[nxt]==c:
            return False
    return True

for i in range(0,n):
    if color[i]==NIL:
        if dfs(i,RED)==False:
            print("No")
            sys.exit()
print("Yes")