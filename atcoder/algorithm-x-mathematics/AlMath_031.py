'''アルゴリズムと工夫点(Taro's Vacation/CPU: 167 ms Memory: 170156 KB  Length: 338 B)
dp[i][j]=i+1日まで勉強するかしないか決めた時，状態j∈{0(i日目に勉強していない),1(i日目に勉強した)} で最大の実力上昇量
とする動的計画法で解ける．
最悪計算量は O(2*N)≒10^6 となり十分高速．
'''
n=int(input())
a=list(map(int,input().split()))
last=[0 for _ in range(0,2)]#(last[0],last[1]):(前日勉強しなかった時の最大値,前日勉強した時の最大値)
for aa in a:
    now=[last[i] for i in range(0,2)]
    now[1]=max(now[1],last[0]+aa)
    now[0]=max(now[0],last[1])
    last=now
print(max(last[0],last[1]))