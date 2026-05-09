'''アルゴリズムと工夫点(Dice Expectation/CPU: 85 ms Memory: 107232 KB  Length: 325 B)
Bi,Riの値が小さいため，和の値としてとり得る範囲が，0~200の201通りしかないため，こちらを全列挙する．
「AlMath_022.py」と同様の「主客転倒」のアルゴリズム．今夏の問題のように極端に小さい制約があれば，それを元にアルゴリズムを組み立てることはよくある．
最悪計算量は O(N+max(Ri)*max(Bi))<10^6 となり十分高速．
※「和の期待値」は「期待値の和」であるという期待値の線型性を用いれば，Ri,Biに依存せずO(N)で解けるという，強力なアルゴリズム．
※確率変数X,Yそれぞれの期待値E[X],E[Y]，P(X=Xi)=Pi,P(Y=Yj)=Pjとすると，E[X+Y]=Σ(0<=i<N)Σ(0<=j<M)(Xi+Yj)Pi*Pj=Σ(0<=j<M)Pj*Σ(0<=i<N)Pi*Xi+Σ(0<=i<N)Pi*Σ(0<=j<M)PjYj=E[X]+E[Y]
'''
MAX_B=100
MAX_R=100
cntB=[0]*(MAX_B+1)
cntR=[0]*(MAX_R+1)
ans=0
n=int(input())
b=list(map(int,input().split()))
r=list(map(int,input().split()))
for i in range(0,n):
    cntB[b[i]]+=1
    cntR[r[i]]+=1
for i in range(0,MAX_B+1):
    for j in range(0,MAX_R+1):
        ans+=(i+j)*cntB[i]*cntR[j]
print(ans/(n*n))