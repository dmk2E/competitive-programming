'''アルゴリズムと工夫点(Large LCM（★3）/CPU: 54 ms Memory: 80060 KB  Length: 405 B)
条件式の式変形により解く．
和や積の計算は，その値によりオーバーフローが発生してしまう場合がある．
対策として，商の形に式変形を行う．
今回の場合，2つの整数A, B の最大公約数 GCM(A, B) とすると，最小公倍数 LCM(A, B) について，
A * B = GCM(A, B) * LCM(A, B) となり，LCM(A, B) = A * B / GCM(A, B) となる．
LCM(A, B) < 10 ^ 18 であるかの判定では，両辺Bで割った形で考えて，
A / GCM(A, B) < floor(10 ^ 18 / B) という形で条件判定を行えばよい．
最悪計算量は，O(log2(B)) < 10 ^ 2 となり十分高速．
※ 多倍数整数が実装されている Python では，今回行ったオーバーフロー対策は不要
※ 条件式の式変形について詳しく知りたい方は，下記の Qiita の記事を参照してください
※  - https://qiita.com/dmk2E/items/a0257b7cbce9413f09e5
'''
import sys

a, b = 0, 0
INF = 1000000000000000000

def gcd(a: int, b: int) -> int: 
    return a if b == 0 else gcd(a=b, b=a % b)

def main(argv: list[str]):
    global n
    a, b = map(int, input().split())
    ab_gcd = gcd(a=a, b=b)
    if a // ab_gcd > INF // b: 
        print("Large")
    else: 
        # aはab_gcdで割り切れるため，a // ab_gcd を先に計算することで，
        # オーバーフローを回避できる
        print((a // ab_gcd) * b)
if __name__ == "__main__":
    main(argv=sys.argv[1:])