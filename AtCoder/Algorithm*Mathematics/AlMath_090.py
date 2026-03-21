'''アルゴリズムと工夫点(Digit Product Equation（★7）/CPU: 209 ms Memory: 119032 KB  Length: 1075 B)
再帰を用いた全探索により解く．
f(m) のとり得る値の種類は小さいため，f(m)を全列挙する．
この時，各桁の値は先頭から単調増加することを仮定しても，一般性を失わない．
こうすることで高速で全列挙を実装可能．
'''
import sys
from collections import defaultdict as dict
from typing import DefaultDict

MAX_N_DIGIT = 11

n, b = 0, 0

def digit_product(x: int) -> int: 
    if x == 0: 
        return 0
    str_x = str(x)
    ans = 1
    for c in str_x: 
        ans *= int(c)
    return ans

def rec(digit: int, prev: int, product: int, is_exist: DefaultDict[int, bool]) -> int:
    global n, b
    cnt = 0 
    if digit > 0: 
        if not is_exist[product]: 
            is_exist[product] = True
            m = b + product
            cnt += 1 <= m and m <= n and digit_product(m) == product
    if digit < MAX_N_DIGIT: 
        for val in range(prev, 10): 
            cnt += rec(
                digit=digit + 1, 
                prev=val, 
                product=product * val, 
                is_exist=is_exist
            )
    return cnt

def main(argv: list[str]):
    global n, b
    n, b = map(int, input().split())
    print(rec(digit=0, prev=0, product=1, is_exist=dict(bool)))

if __name__ == "__main__":
    main(argv=sys.argv[1:])