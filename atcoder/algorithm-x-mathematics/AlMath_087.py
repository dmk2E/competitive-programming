'''アルゴリズムと工夫点(Simple Math Easy/CPU: 52 ms Memory: 80012 KB  Length: 215 B)
式変形により，単純な式に変形して解く．
Σ(i ∈ [1, N])Σ(j ∈ [1, N]) i * j = (1 + 2 + 3 + ...) * (1 + 2 + 3 + ...) 
                                 = (n * (n + 1) / 2) ^ 2
最悪計算量は，O(1) となり十分高速．
'''
import sys
MOD = 1000000007 

n = 0

def main(argv: list[str]):
    global n
    n = int(input())
    print((((n * (n + 1) // 2) % MOD) ** 2) % MOD)

if __name__ == "__main__":
    main(argv=sys.argv[1:])
 