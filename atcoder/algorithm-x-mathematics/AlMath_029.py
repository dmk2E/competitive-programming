'''アルゴリズムと工夫点(Climb Stairs/CPU: 64 ms Memory: 76668 KB  Length: 169 B)
動的計画法は，解法を思いつくまでの思考プロセスを大事にして精進するのが良い．
'''
n=int(input())
dp=[0 for _ in range(0,n+1)]
dp[0]=1
for i in range(0,n):
    if i+1<=n:
        dp[i+1]+=dp[i]
    if i+2<=n:
        dp[i+2]+=dp[i]
print(dp[n])