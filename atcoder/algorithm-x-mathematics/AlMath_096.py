'''アルゴリズムと工夫点(Cooking/CPU: 145 ms Memory: 167728 KB  Length: 707 B)
動的計画法で解く．
N品の料理を2つのオーブンで全て作る際の最短時間は，各オーブンの使用時間の差が最小であればよい．
そこで，1つのオーブンで1~N個の料理を作る際，有り得る使用時間tiを全探索することを考える．
すると，全N料理のオーブンの使用時間の総和 sum_t とすると，片方のオーブンの使用時間がtiであった時，
N品全て作るのに max(ti, sum_t - ti) だけの時間がかかり，この最小値を出力すればよい．
1つのオーブンの使用時間の全列挙は，下記の動的計画法を用いることで解ける．
dp[i][j] := (1 ~ i+1番目までの料理を作った時に，使用時間の合計がjとなり得るか)
最悪計算量は，O(max(T) * N ^ (2)) < 10 ^ 8 となり間に合う．
'''
import sys

MAX_T = 1000

n = 0
t = []

def main(argv: list[str]):
    global n, t

    n = int(input())
    t = list(map(int, input().split()))
    MAX_SUM_T = MAX_T * n
    dp = [False] * (MAX_SUM_T + 1)
    sum_t = 0
    dp[0] = True
    for i in range(n): 
        now = [False] * (MAX_SUM_T + 1)
        for j in range(MAX_SUM_T): 
            if dp[j]: 
                now[j] = True
                now[j + t[i]] = True
        sum_t += t[i]
        dp, now = now, dp
    
    ans = MAX_SUM_T + 1
    for j in range(MAX_SUM_T + 1): 
        if dp[j]: 
            ans = min(ans, max(j, sum_t - j))
    print(ans)

if __name__ == "__main__":
    main(argv=sys.argv[1:])