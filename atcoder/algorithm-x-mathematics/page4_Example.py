'''アルゴリズムと工夫点(4ページ目の最大カロリー計算問題/CPU: - ms Memory: - KB  Length: - B)
4ページ目の問題を以下のように一般化する．
----------------------
あるコンビニにはN個の商品が売られており，それぞれ値段はA円，カロリーKkcalとなる．
M円以内で買い物をするとき，最大で何Kcalを摂取することができるか．
入力は以下の形式で与えられる．
-----------
N M
A1 K1
A2 K2
...
Ak Nk
-----------
入力例1
6 60
50 600
20 230
10 110
10 110
10 110
10 110

出力例1
710

制約:
1<=N<=100
1<=M<=1000000
1<=K<=1000
1<=Ai<=1000000000
----------------------
'''

'''
解説:
単純な全探索を行うと，本書で述べられているように2^N通りの選び方があり，今回Nの制約は最大100と大きいため，この方法は適さない(Nが最大20個位なら全列挙可)．
そこで，「1円当たりのカロリーvが大きい順に摂取すれば良いのでは？」と思った人もいるかもしれない．
このような目先のことだけ考えるアルゴリズムを「貪欲法」といい，貪欲法はほとんどの場合高速に処理される．
しかし，今回の問題では上手く動作出来ない．なぜなら次のようなケースが存在するからだ．
-------------
5 4
1 14
4 52
4 40
4 8
4 4
-------------
このケースでは，1つ目の商品が最もvが大きいため，1つ目を選んでしまうが，そうすると最適解の「4,52」の商品を選べなくなってしまう．

よって，今回の問題では結局全部調べるしかない．
この時，効率的な全探索をする必要があるが，それが「動的計画法」というもの．

-分かる人向けに簡単に解説---------------
dp[i][j]:1つ目～(i+1)つ目の商品の中でいくつか選んだ時，カロリーがjとなるための最小の金額
とする動的計画法で解ける．
このDPテーブル上で，dp[N-1]の列を，jの降順に見ていき，初めてM円以下となるjが解となる．
----------------------------------------
pythonでは多倍数表現がされているため，オーバーフローの心配はないが，C++はオーバーフローに気を付けること．

このように，アルゴリズムを知っていると，機械を用いて高速に最適解を出すことが可能になる．
「動的計画法」についてもこの参考書で扱っているので，詳しくはここでは割愛する．
皆さんとの「参考書精進」の活動を通じて，メンバー全員が一定レベル以上のアルゴリズム考案力を身に着けられるよう，頑張っていきましょう．
'''
MAX_K=1000
MAX_M=1000000

#functions
def dynamicProgramming(ipt,m):#動的計画法:O(max(ki)*N^2)
    #初期化
    NIL=-1
    last=[MAX_M*len(ipt)+1 for _ in range(0,len(ipt)*MAX_K+1)]
    prev=[]
    for i in range(0,len(ipt)+1):
        prev.append([NIL for _ in range(0,len(last))])
    #DPテーブル作成
    last[0]=0
    id=0
    for a,k in ipt:
        now=[last[i] for i in range(0,len(last))]
        prev[id+1]=[prev[id][i] for i in range(0,len(last))]
        for j in range(0,len(last)):
            if j+k>=len(last):
                break
            if now[j+k]>last[j]+a:
                now[j+k]=last[j]+a
                prev[id+1][j+k]=j
        last,now=now,last
        id+=1
    #DPテーブルから最大値探索
    maxK=0
    for i in range(0,len(last)):
        if last[len(last)-1-i]<=m:
            maxK=len(last)-1-i
            break
    #DP復元
    ans=[]
    i=len(ipt)
    k=maxK
    while i>0:
        if prev[i-1][k]!=prev[i][k]:
            ans.append(i)
            k=prev[i][k]
        i-=1
    ans.reverse()
    ans=tuple(ans)
    print(f"DP:{maxK} {ans}",end=" ")
    return maxK

def greedyAlgorithm(ipt,m):#貪欲法:O(N*log2(N))
    class data:
        id,a,k=(0,0,0)
        def __init__(self,iid,aa,kk):
            self.id=iid
            self.a=aa
            self.k=kk

        def __lt__(self,other):
            return self.k*other.a < other.k*self.a

    tmp=[data(i,ipt[i][0],ipt[i][1]) for i in range(0,len(ipt))]
    tmp.sort(reverse=True)
    ans=[]
    maxK=0
    for d in tmp:
        if m>=d.a:
            m-=d.a
            maxK+=d.k
            ans.append(d.id+1)
    ans.sort()
    ans=tuple(ans)
    print(f"Greedy:{maxK} {ans}")
    return maxK

#main
n,m=map(int,input().split())
ipt=[]
for _ in range(0,n):
    id,a,k=(0,0,0)
    ipt.append(list(map(int,input().split())))
# for i in range(0,n):
#     print(f"{ipt[i][0]},{ipt[i][1]}")
dynamicProgramming(ipt,m)
greedyAlgorithm(ipt,m)

'''
テストケース集
6 60
50 600
20 230
10 110
10 110
10 110
10 110

5 5
3 400
1 120
2 230
4 300
5 250

5 4
4 52
4 40
4 8
4 4
1 14

30 1451
120 144
164 174
128 211
30 53
134 122
452 333
345 123
132 234
178 232
234 123
131 245
235 341
264 236
117 227
173 445
300 234
233 346
341 765
234 100
125 113
256 114
600 223
123 124
555 263
222 153
421 254
378 341
333 241
777 5000
1234567 1234567

30 1452
120 144
164 174
128 211
30 53
134 122
452 333
345 123
132 234
178 232
234 123
131 245
235 341
264 236
117 227
173 445
300 234
233 346
341 765
234 100
125 113
256 114
600 223
123 124
555 263
222 153
421 254
378 341
333 241
777 5000
1234567 1234567

5 500
200 125
100 235
300 575
100 165
100 175
'''