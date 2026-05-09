'''アルゴリズムと工夫点(Depth First Search/CPU: 687 ms Memory: 626592 KB  Length: 542 B)
-グラフの表現方法について--
グラフの表現方法は，以下の2通りあり，両方とも覚えておこう．
・隣接行列：二次元配列adjで表現され，頂点iからj向かって有向辺が存在する場合，重み無しグラフならadj[i][j]=1,存在しないならadj[i][j]=0
重みが存在するなら重みの値を代入する．無向グラフなら，隣接行列は対称行列になる．
利点：辺の削除，2頂点間の辺の存在判定がO(1)
欠点：空間計算量（メモリ消費量）がO(N^2)

・隣接リスト：可変長配列の配列adjで表され，頂点iを始点とする頂点jへの有向辺の集合はadj[i]に格納される
利点：空間計算量に無駄がなく，O(N+M)
欠点：辺の削除，2頂点間の辺の存在判定の最悪計算量がO(M)

-本題--
深さ優先探索の実装はスタックでも可能だが，再帰を使った方が楽で実装も軽くなる．
今回は，ある任意の2頂点が連結であるかの判定用配列colorを作成する方針で解いた．
連結成分ごとに異なる色を割り当てるイメージで，コードの様に実装でき，同じ連結成分なら同じ色が割り当てられる．
今回の問題では，割り当てた色の数が1種類のみであるなら全て連結であると判定できる．
※pythonでは，再帰を用いる場合，再帰の呼び出し制限を十分大きい数に設定しておくこと．設定しないとREになる
※ただし，再帰を使うと基本実行は遅くなるため，色塗り程度ならBFS（幅優先探索）での実装をおすすめする．
※global文は，グローバル変数を"参照"するだけなら必要ない．
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

c=0
NIL=-1
color=[NIL for _ in range(0,n)]

def dfs(now:int,c:int):
    color[now]=c
    for nxt in adj[now]:
        if color[nxt]==NIL:
            dfs(nxt,c)

for i in range(0,n):
    if color[i]==NIL:
        dfs(i,c)
        c+=1

print("The graph is connected." if c==1 else "The graph is not connected.")