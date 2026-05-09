'''アルゴリズムと工夫点(Snowy Days/CPU: 119 ms Memory: 85848 KB  Length: 357 B)
imos法の典型問題．
最悪計算量は O(N+Q)<10^6 となり十分高速．
※典型:区間の加減算が複数回行われた後の，最終結果のみが知りたい->imos法（更新:O(1) 最終結果計算:O(N)）
※途中段階の区間和も知りたい場合は，「遅延セグ木」と呼ばれるデータ構造を用いればよい．
このデータ構造では，区間更新と区間和の取り出しをO(log2(N))で行える．
'''
n,q=map(int,input().split())
a=[0]*n

while q>0:
    q-=1
    l,r,x=map(int,input().split())
    a[l-1]+=x
    if r<n:
        a[r]-=x

for i in range(0,n-1):
    a[i+1]+=a[i]

for i in range(0,n-1):
    if a[i]>a[i+1]:
        print('>',end="")
    elif a[i]<a[i+1]:
        print('<',end="")
    else:
        print('=',end="")
print()