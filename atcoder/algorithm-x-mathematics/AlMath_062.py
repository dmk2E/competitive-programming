'''アルゴリズムと工夫点(Teleporter/CPU: 272 ms Memory: 206392 KB  Length: 430 B)
ダブリングで高速化して解く．
町を頂点とし，テレポーターでの移動を辺で表現した有向グラフを考える．
町1の連結成分の個数Xを求めると，頂点1からk%X だけ進んだ先が，求める到着先となる．
これはBFSなどを用いれば簡単に実装可能で，最悪計算量は，O(N)

今回は，捉えたグラフがfunctional-graphになる場合に有効なアルゴリズムである，「ダブリング」を用いて解いた．
最悪計算量は，O(N*log2(K)) < 10^7 となり高速．
※計算量は悪化するが，任意の町から2^(i)回移動した到着先を，前処理で求めておくことが可能で，様々な場面で有用であるため覚えておこう．
※参考資料 - https://zenn.dev/fjnkt98/articles/3c0c21778b6101
'''
MAX_DIGIT = 60
n,k = map(int,input().split())
dp = [[0 for _ in range(n)] for _ in range(MAX_DIGIT)]
# 0-indexed に
dp[0] = [a-1 for a in map(int,input().split())]
# 前処理（ダブリング）
for i in range(MAX_DIGIT-1):
    for j in range(n):
        dp[i+1][j] = dp[i][dp[i][j]]
# 高速シミュレーション
now = 0
for i in range(MAX_DIGIT):
    if (k>>i) & 1:
        now = dp[i][now]
print(f"{now+1}")