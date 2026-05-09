'''アルゴリズムと工夫点(Two Conditions/CPU: 65 ms Memory: 87892 KB  Length: 1162 B)
一般性を失わない条件を付与し，全探索．
条件式には対称性が存在するため，下記の条件を加えても一般性を失わない
* a <= b <= c <= d
こうすることで，整数a, b, cは下記のように探索範囲を絞ることが出来る
Y = abcd >= a ^ 4 ∴ a <= Y ^ (1 / 4)
Y / a = bcd >= b ^ 3 ∴ b <= (Y / a) ^ (1 / 3)
Y / (a * b) = cd >= c ^ (2) ∴ c <= (Y / (a * b)) ^ (1 / 2)
...

最悪計算量は，O(Y ^ (1 / 4) * (log2(Y)) ^ 2) < 10 ^ 6 となり十分高速．
'''
import sys

n, x, y = 0, 0, 0

def judge() -> bool: 
    global n, x, y
    # aの値を固定する
    a = 1
    while a * a <= y // (a * a): 
        if a > n:
            break
        if y % a == 0: 
            y_div_a = y // a

            # bの値を固定する
            b = a
            while b * b <= y_div_a // b:
                if b > n: 
                    break 
                if y_div_a % b == 0: 
                    y_div_ab = y_div_a // b

                    # cの値を固定する
                    c = b
                    while c <= y_div_ab // c:
                        if c > n: 
                            break
                        if y_div_ab % c == 0: 
                            d = y_div_ab // c
                            if d <= n and a + b + c + d == x: 
                                return True
                        c += 1
                b += 1
        a += 1
    return False

def main(argv: list[str]):
    global n, x, y
    n, x, y = map(int, input().split())
    print("Yes" if judge() else "No")

if __name__ == "__main__":
    main(argv=sys.argv[1:])
