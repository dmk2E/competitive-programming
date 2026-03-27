'''アルゴリズムと工夫点(Maximal Value/CPU: 58 ms Memory: 80120 KB  Length: 370 B)
先頭から順次値を求めていく．
各要素Ai について，満たさなければならない条件は，B_i以下かつB_{i + 1}以下である．
従って，各Aiの最大値は，Ai = min(B_i, B_{i + 1}) となり，順次求めていけば，最悪計算量は，O(N) < 10 ^ 3 となり十分高速．
'''
import sys

MAX_B = 100000

n = 0
b = []

def main(argv: list[str]):
    global n, b
    n = int(input())
    b = list(map(int, input().split()))
    ans = [MAX_B + 1] * n
    for i in range(n - 1):
        ans[i] = min(ans[i], b[i])
        ans[i + 1] = min(ans[i + 1], b[i])
    print(sum(ans))

if __name__ == "__main__":
    main(argv=sys.argv[1:])