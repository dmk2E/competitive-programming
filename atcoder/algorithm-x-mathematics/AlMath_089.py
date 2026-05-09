'''アルゴリズムと工夫点(Log Inequality 2/CPU: 53 ms Memory: 80060 KB  Length: 589 B)
式変形により，整数型の演算子気に変形して解く．
log2(a) < b * log2(c) ⇔ log2(a) < log2(c ^ b)
両辺正より，a < c ^ b
c ^ b の値は繰り返し二乗法を用いて段階的に値を求めていき，
計算途中で c ^ (?) の値がaの値を超えたら計算終了することで，高速化している．
最悪計算量は，O(log2(b)) < 10 ^ 3 となり十分高速．
※ 公式解説では，c = 1 を例外ケースとして，c ^ b を愚直に計算して判定していた
'''
import sys

a, b, c = 0, 0, 0

def judge() -> bool: 
    global a, b, c
    mul = c
    now_b = b
    now_c = 1
    while now_b > 0: 
        if now_b & 1: 
            if now_c > a // mul: 
                return True
            now_c *= mul
        now_b >>= 1
        if (now_b >> 1) > 0 and mul > (a + mul - 1) // mul:
            return True
        mul *= mul
    return False

def main(argv: list[str]):
    global a, b, c
    a, b, c = map(int,input().split())
    print("Yes" if judge() else "No")

if __name__ == "__main__":
    main(argv=sys.argv[1:])
