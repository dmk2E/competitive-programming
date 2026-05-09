'''アルゴリズムと工夫点(Small Multiple/CPU: 831 ms Memory: 125388 KB  Length: 564 B)
一般的に整数は，「10倍して1~9の値を足す」という操作の繰り返しによって作ることができる．
この操作で整数を作成していくことで，桁和を簡単に求めることができる．
従って，桁和の増加量を重みとする重み付きグラフ上での最短経路問題を解けばよい．
重みがあるグラフ上での最短経路はダイクストラ法での実装となる．
何も見ずに書けるよう，練習しよう．
※最初の「0」は値を更新しないなど，工夫が必要で，初見で解けませんでした...
※典型：「kの倍数->整数をkの余りで分類」
'''
import heapq
k=int(input())

def dijk(k:int)->int:
    PQ=[]
    is_first=True
    NIL=-1
    vis=[NIL]*k
    heapq.heappush(PQ,(0,0))
    while len(PQ)>0:
        cost,now=heapq.heappop(PQ)
        if vis[now]!=NIL:
            continue
        if is_first==False:
            vis[now]=cost
        is_first=False
        if now>0:
            heapq.heappush(PQ,(cost,(now*10)%k))
        for i in range(1,10):
            if vis[(now*10+i)%k]==NIL:
                heapq.heappush(PQ,(cost+i,(now*10+i)%k))
    return vis[0]

print(dijk(k))