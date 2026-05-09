'''アルゴリズムと工夫点(Sum of Maximum/CPU: 185 ms Memory: 146796 KB  Length: 470 B)
最大値を固定した時の選び方を数え上げる，全探索で解く．
あるAiが最大値となる選び方は，Aiより小さい要素の数 M とすると，2 ^ (M) 通りとなる．
これを利用し，全要素を最大値として固定した時の場合の数の総和を求める．
最悪計算量は，O(N * log2(max(A))) < 10 ^ 7 となり高速．
※ 今回は繰り返し二乗法を用いたが，2 ^ N の値は連続性があるため，順次求める形を取れば O(N) で解ける．
'''
MOD = 1000000007

def power(x: int, a: int) -> int:
    """
    x ^ a を繰り返し自乗法を用いて計算

    params:
        x: 被乗数
        a: べき数
    """
    ans = 1
    while a > 0:
        if a & 1 == 1:
            ans *= x
        x = (x * x) % MOD
        a >>= 1
    return ans

n = int(input())

ans = 0
for i, a in enumerate(list(map(int, input().split()))):
    ans = (ans + (a * power(2, i)) % MOD) % MOD
print(ans)