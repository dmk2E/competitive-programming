'''アルゴリズムと工夫点(Tricolor Pyramid/CPU: 361 ms Memory: 109668 KB  Length: 753 B)
リュカの定理を用いて解く．
青・白・赤それぞれにID，0, 1, 2 を割り当てると，
ブロックIDがx, yの2ブロックの上のブロックに割り当てられるIDは，-(x + y) mod 3 と計算できる．
これを利用すると，一番上のブロックに割り当てられるIDは二項係数を用いた多項式で表される．
この計算はリュカの定理を用いることで高速化できる．
詳しくは公式解説を見て下さい．
※ 規則性の考察の為，状態を数値で表し，数値計算で状態の変化を表す場合がある
'''
import sys

n = 0
s = ""

def combMod3(n: int, r: int) -> int: 
    if n < 3 and r < 3: 
        if n < r: 
            return 0
        if n == 2 and r == 1: 
            return 2
        return 1
    return combMod3(n=n // 3, r=r // 3) * combMod3(n=n % 3, r=r % 3)

def main(argv: list[str]):
    global n, s
    n = int(input())
    s = input()
    ans = 0
    for i in range(n): 
        code = 0
        if s[i] == 'B': 
            code = 0
        elif s[i] == 'W': 
            code = 1
        else:
            code = 2
        ans += code * combMod3(n=n - 1, r=i)
        ans %= 3
    if n % 2 == 0: 
        ans = (3 - ans) % 3
    print("BWR"[ans])

if __name__ == "__main__":
    main(argv=sys.argv[1:])
