'''アルゴリズムと工夫点(How Many Guests?/CPU: 240 ms Memory: 105108 KB  Length: 201 B)
累積和の典型問題．前処理O(N)だが，区間和の取り出しがO(1)で行える．
最悪計算量は O(N+Q)<10^6 となり十分高速．
※典型:「値の変更がない配列上で，区間の和を高速に求めたい->累積和」
'''
n,q=map(int,input().split())
a=list(map(int,input().split()))
sum=[0]

for aa in a:
    sum.append(sum[-1]+aa)

while q>0:
    l,r=map(int,input().split())
    print(sum[r]-sum[l-1])
    q-=1