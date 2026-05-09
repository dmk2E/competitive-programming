'''アルゴリズムと工夫点(Brute Force 2/CPU: 65 ms Memory: 81536 KB  Length: 372 B)
1000点満点のためには，動的計画法を用いる必要があるが，今回のメインは「ビット全探索」をマスターすること．
ビット全探索の詳しい説明は「サークル共有ファイル」を参照してください．
・ビット全探索
各整数を取るか，取らないかの2通りのパターンがあるので，最悪計算量はO(N*2^(N))≒10^(19)>10^8 となり，今回の問題では間に合わない．
500点獲得コース

・動的計画法で解く場合(分かる人向け，3.7節用)
dp[i][j]:A[1,i)で，いくつかの整数を選んだ時，合計がちょうどSになるか
という動的計画法で解くことができる．
dp[i+1]の各値はdp[i]の情報とa[i]の値のみがあればよいから，lastとnowでDPテーブル2行分だけ持つことで，メモリを節約している．

※pythonにおけるデータ構造の代入は，「参照の代入」であり，新たにメモリを確保したコピーではないことに注意．
'''
n,s=map(int,input().split())
a=list(map(int,input().split()))
last=[False]*(s+1)
last[0]=True
now=[last[i] for i in range(0,s+1)]
for i in range(0,n):
    for j in range(0,s+1):
        if j+a[i]>s:
            break
        if last[j]:
            now[j+a[i]]=True
    last=[now[k] for k in range(0,s+1)]
if last[s]:
    print("Yes")
else :
    print("No")

#ビット全探索で解く場合
# def bitBruteSearch(n,s,a)->str:
#     i=0
#     sum=0
#     for now in range(0,1<<n):
#         i=sum=0
#         while (1<<i)<=now:
#             if (1<<i)&now:
#                 sum+=a[i]
#             i+=1
#         if sum==s:
#             return "Yes"
#     return "No"

# n,s=map(int,input().split())
# a=list(map(int,input().split()))
# print(bitBruteSearch(n,s,a))