'''アルゴリズムと工夫点(Choose Cards 3/CPU: 77 ms Memory: 99564 KB  Length: 312 B)
「1枚目のカードとして，どれを選ぶか」「2枚目のカードとして，どれを選ぶか」という「選ぶor選ばない」という風に探索空間を見てしまうと，全列挙では，N^2 通り存在してしまい，間に合わない．
ここで，カードの値そのものに着目する．合計sumが固定されているため，2枚のカードの内片方の値が決まると，もう片方の値も決まる．
a+b=sum(a<=b) を満たす時，sumとなるカードの選び方は，(aを値として持つカード枚数)*(bを値として持つカード枚数)(a=bの時は，/2する) となる．
この列挙の仕方では，高々sum/2通りしか存在しないから，最悪計算量は O(sum)≒10^6 となり十分高速．
※この探索空間を捉え直すアルゴリズム(考え方そのもの?)を，「主客転倒」という．
'''
MAX_A=99999
sum=100000
n=int(input())
a=map(int,input().split())
a2Cnt=[0]*(MAX_A+1)
for aa in a:
    a2Cnt[aa]+=1
ans=0
for i in range(1,sum//2):
    ans+=(a2Cnt[i]*a2Cnt[sum-i])
if sum%2==0:
    ans+=(a2Cnt[sum//2]*(a2Cnt[sum//2]-1))//2
else:
    ans+=(a2Cnt[sum//2]*a2Cnt[sum-sum//2])
print(ans)