'''アルゴリズムと工夫点(How Many Ways?/CPU: 72 ms Memory: 86836 KB  Length: 534 B)
全探索で解く．
最悪計算量は，O(N ^ 2) < 10 ^ 6 となり十分高速．
'''
import sys

n, x = 0, 0

def main(argv: list[str]):
    global n, x
    ans = 0
    n, x = map(int, input().split())
    for a in range(1, n + 1): 
        for b in range(a + 1, n + 1): 
            c = x - a - b
            ans += b < c and c <= n
    print(ans)

if __name__ == "__main__":
    main(argv=sys.argv[1:])