'''アルゴリズムと工夫点(Choose Cards 2/CPU: 66 ms Memory: 81764 KB  Length: 464 B)
5つ選ぶ方法は，nC5通り存在し，係数が1/5!=1/120 となるため，最悪計算量は10^8未満になるから，全探索で求めることは可能．
この解法は参考書を参照のこと．

今回は，制約が 「5<=N<=10000,1<=Ai<=1000」 だった時の解法を考える．
dp[i][j][k]:1~(i+1)番目までの商品からj個選んだ時，その総和がSとなる選び方の総数
とする動的計画法で解ける．
最悪計算量は O(N*5*max(Ai))<10^8 となり，高速．
↑C++ なら余裕だが，python だと，間に合わないかも...
'''
MAX_A=1000
NUMBER=5

n=int(input())
a=list(map(int,input().split()))

last=[]
for _ in range(0,NUMBER+1):
    last.append([0]*(MAX_A+1))
last[0][0]=1
for aa in a:
    #最新のDPテーブル確保
    now=[]
    for i in range(0,len(last)):
        now.append([x for x in last[i]])
    #DPテーブルの遷移
    for i in range(0,NUMBER):
        for j in range(0,len(last[i])):
            if last[i][j]>0 and j+aa<=MAX_A:
                now[i+1][j+aa]+=last[i][j]
    last=now
print(last[NUMBER][MAX_A])