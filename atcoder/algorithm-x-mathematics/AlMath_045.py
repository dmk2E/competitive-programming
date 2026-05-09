'''アルゴリズムと工夫点(Easy Graph Problem（★2）/CPU: 205 ms Memory: 97060 KB  Length:  B)
グラフを隣接リストの形で保持すれば，慣らし計算量O(N+M)<10^7 で解ける．
'''
n,m=map(int,input().split())
adj=[[] for _ in range(0,n)]

while m>0:
    a,b=map(int,input().split())
    adj[a-1].append(b-1)
    adj[b-1].append(a-1)
    m-=1

ans=0
def judge(now:int)->bool:
    cnt=0
    for nxt in adj[now]:
        if nxt<now:
            cnt+=1
    return cnt==1

for i in range(0,n):
    ans+=judge(i)
print(ans)