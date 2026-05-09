'''アルゴリズムと工夫点(A x B + C/CPU: 57 ms Memory: 76860 KB  Length: 184 B)
A<=B としても一般性を失わないから，A^(2)<=A*B<A*B+C=N より，A<=√N
Aを固定すると，B ∈ [A,N] であるから，"正の整数Cが存在するBの範囲"を探索することを考える．
Cが存在する条件Pは，C=N-A*B>0 つまり，A*B < N 
よって，この条件を満たすBの範囲の大きさが，Aの値を固定した時の条件を満たす (A,B,C) (A<=B) の組の数となる．
求める組では，A,B,Cに関して条件は付与されていないため，そこもきちんと考慮して数え上げる．

条件Pにおいて，Aの単調増加に対して，Bは単調減少するため，尺取り法により高速化が可能．
最悪計算量は O(N)≒10^6 となり十分高速．
 ||
 \/
また条件Pにおいて，A, Nは定数であるから，Bの増加に関して単調性が存在する->二分探索 が可能．
従って最悪計算量は，O(√N*log2(N))≒10^4<10^6 となり十分高速．
 ||
 \/
よくよく考えると，二分探索するまでもなく，A*B<N を満たすBの最大値は，N/A 付近になる．
したがって，最悪計算量は，O(√N)≒10^3 となり十分高速．

※計算時間チェック (実行環境:https://atcoder.jp/contests/practice/custom_test)
N=100000000
answer:1857511487

O(√N):59 ms
O(√N*log2(N)): 61 ms
O(N): 345 ms

N=1000000000000
answer:27785452448917

O(√N): 64 ms
O(√N*log2(N)): 271 ms
O(N): Time Limit Exceeded

N=100000000000000
answer:3239062263180829

O(√N): 119 ms
O(√N*log2(N)): 2342 ms
O(N): Time Limit Exceeded

※問題リンク
https://atcoder.jp/contests/abc179/tasks/abc179_c
'''
n=int(input())
ans=0

a=1
while a<(n+a-1)//a:# pythonでは気にしなくていいが，オーバーフロー対策としてa*a<=n から商の形に式変形 
    # aの値を固定した時，a*b<n を満たすbの最大値max_b は，"floor(n/a)", または "floor(n/a)-1"
    max_b=n//a
    if a>=(n+max_b-1)//max_b:# pythonでは気にしなくていいが，オーバーフロー対策としてa*max_b>=n から商の形に式変形
        max_b-=1
    ans+=(max_b>=a)
    # a<b なら，組の数は，(a,b,c)と(b,a,c)の2通り
    ans+=max(max_b-a,0)*2
    a+=1
print(ans)

''' 二分探索Ver:CPU: 63 ms Memory: 81404 KB  Length: 282 B
n=int(input())
ans=0

a=1
while a<=n//a:# pythonでは気にしなくていいが，オーバーフロー対策としてa*a<=n から商の形に式変形 
    # aの値を固定する
    left=a
    right=n
    while left<right:
        mid=(left+right)//2
        if a<(n+mid-1)//mid:# pythonでは気にしなくていいが，オーバーフロー対策としてa*mid<n から商の形に式変形
            left=mid+1
        else:
            right=mid
    # 二分探索により，この時点で，b∈[a,left) では条件を満たす．
    # a=b なら，組の数は1通り left==a の場合，a=bの時点で条件Pを満たさないことに注意．
    ans+=(left>a)
    # a<b なら，組の数は，(a,b,c)と(b,a,c)の2通り
    ans+=max(left-a-1,0)*2
    a+=1
print(ans)
'''
'''
# 尺取り法Ver CPU: 63 ms Memory: 81052 KB  Length: 243 B
import math

n=int(input())

ans=0
a=1
max_b=n
while a<=n//a:
    while a<=max_b and a>=(n+max_b-1)//max_b:
        max_b-=1
    if a>max_b:
        break
    if a<=max_b:
        ans+=1
    ans+=(max_b-a)*2
    a+=1
print(ans)
'''