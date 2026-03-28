'''アルゴリズムと工夫点(Primes in an Interval/CPU: 146 ms Memory: 112136 KB  Length: 836 B)
エラトステネスの篩を，[L, R] の範囲で実行する．
最悪計算量は，O((R - L) * log2(R - L)) < 10 ^ 7 となり十分高速．
'''
import sys

l, r = 0, 0

def main(argv: list[str]):
    global l, r
    l, r = map(int, input().split())

    len = r - l + 1
    is_prime = [True] * len
    ans = len
    if l == 1:
        is_prime[0] = False
        ans -= 1
    i = 2
    while i <= r // i:
        # 着目する値が篩の配列上に存在しない場合
        if i < l: 
            j = (i - l % i) % i
            while j < len: 
                if is_prime[j]: 
                    is_prime[j] = False
                    ans -= 1
                j += i
        else: 
            # 通常の篩の処理
            if is_prime[i - l]: 
                j = 2 * i - l
                while j < len: 
                    if is_prime[j]: 
                        is_prime[j] = False
                        ans -= 1
                    j += i
        i += 1
    print(ans)

if __name__ == "__main__":
    main(argv=sys.argv[1:])