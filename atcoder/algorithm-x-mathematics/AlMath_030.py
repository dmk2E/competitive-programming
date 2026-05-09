'''アルゴリズムと工夫点(Knapsack 1/CPU: 154 ms Memory: 160356 KB  Length: 292 B)
超有名動的計画法．
参考書をしっかり読んでものにしよう．
※ナップサック問題系は，メモリ節約のため，W個の一次元配列2個で動的計画法を実行できることを覚えておこう．
'''
n,w=map(int,input().split())
last=[0 for _ in range(0,w+1)]
while n:
    ww,v=map(int,input().split())
    now=[last[i] for i in range(0,w+1)]
    for j in range(0,w+1):
        if j+ww<=w and last[j]+v>now[j+ww]:
            now[j+ww]=last[j]+v
    last=now
    n-=1
print(last[w])