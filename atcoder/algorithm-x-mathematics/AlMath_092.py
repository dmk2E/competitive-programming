'''アルゴリズムと工夫点(Beautiful Rectangle/CPU: 66 ms Memory: 85924 KB  Length: 319 B)
効率的な全探索を行う．
縦と横の長さをそれぞれ，a, b とすると，面積がNであるとは，a * b = N を満たす．
ここで，a <= b と考えても，一般性を失わない．
すると，N = a * b >= a ^ 2 ∴ 1 <= a <= √N (∵ a >= 1) となるから，この範囲でaの値を全探索して解けばよい．
最悪計算量は，O(√N) < 10 ^ 7 となり高速．
'''
import sys

n = 0

def main(argv: list[str]):
    global n
    n = int(input())
    ans = 4 * n
    a = 1
    while a <= n // a: 
        if n % a == 0: 
            b = n // a
            ans = min(ans, (a + b) * 2)
        a += 1
    print(ans)

if __name__ == "__main__":
    main(argv=sys.argv[1:])