'''アルゴリズムと工夫点(Travel/CPU: 147 ms Memory: 128756 KB  Length: 343 B)
ある駅から駅までの移動距離は，与えられる配列aの区間和である．
この区間和を高速に求めることができれば，巡回する駅の数は少ないから，単純なシミュレーションで解ける．
最悪計算量は O(N+M)<10^6 となり十分高速．
'''
n=int(input())
a=list(map(int,input().split()))

sum=[0]
for i in range(0,n-1):
    sum.append(sum[-1]+a[i])

m=int(input())
now=int(input())
now-=1
ans=0
m-=1
while m>0:
    nxt=int(input())
    nxt-=1
    if now<nxt:
        ans+=sum[nxt]-sum[now]
    else:
        ans+=sum[now]-sum[nxt]
    now=nxt
    m-=1
print(ans)