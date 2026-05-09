'''アルゴリズムと工夫点(Jiro's Vacation/CPU: 99 ms Memory: 139504 KB  Length: 157 B)
Xi=(i日目の勉強時間) となる確率変数とすると，求める期待値は，E[Σ(1<=i<=N)Xi]=Σ(1<=i<=N)Xi となる．
よって最悪計算量は，O(N)<10^6 より十分高速．
'''
n=int(input())
a=list(map(int,input().split()))
b=list(map(int,input().split()))
ans=0.0
for i in range(0,n):
    ans+=a[i]/3.0+2.0*b[i]/3.0
print(ans)