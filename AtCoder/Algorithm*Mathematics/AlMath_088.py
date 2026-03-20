'''アルゴリズムと工夫点(Simple Math/CPU: 53 ms Memory: 80124 KB  Length: 448 B)
式変形により単純な式にしてから解く．
(与式) = (1 + 2 + ... + A) * (1 + 2 + ... + B) * (1 + 2 + ... + C)
       = (A * (A + 1) / 2) * (B * (B + 1) / 2)) * (C * (C + 1) / 2)
最悪計算量は，O(1) となり十分高速．
'''
import sys
MOD = 998244353

a, b, c = 0, 0, 0

def calc_sum(first: int, last: int) -> int: 
    return (MOD + (last * (last + 1) // 2) % MOD - (first * (first - 1) // 2) % MOD) % MOD

def main(argv: list[str]):
    global a, b, c
    a, b, c = map(int, input().split())
    print(((calc_sum(first=1, last=a) * calc_sum(first=1, last=b)) % MOD * calc_sum(first=1, last=c)) % MOD)

if __name__ == "__main__":
    main(argv=sys.argv[1:])