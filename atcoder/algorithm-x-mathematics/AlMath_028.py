'''アルゴリズムと工夫点(Frog 1/CPU: 88 ms Memory: 96216 KB  Length: 276 B)
漸化式は，動的計画法を考える第一歩．
少しずつマスターしていこう．
'''
n=int(input())
h=list(map(int,input().split()))
INF=int(1e9)
dp=[INF for _ in range(0,n)]
dp[0]=0
for i in range(0,n):
    if i+1<n :
        dp[i+1]=min(dp[i]+abs(h[i]-h[i+1]),dp[i+1])
    if i+2<n:
        dp[i+2]=min(dp[i]+abs(h[i]-h[i+2]),dp[i+2])
print(dp[n-1])