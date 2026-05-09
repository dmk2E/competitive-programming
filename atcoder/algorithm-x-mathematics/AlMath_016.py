'''アルゴリズムと工夫点(Greatest Common Divisor of N Integers/CPU: 77 ms Memory: 96204 KB  Length: 199 B)
高校数学の感覚で解こうとすると，与えられたN個の数値それぞれを素因数分解して，「n個それぞれにおけるその素因数の最小の指数」だけ各素数を累乗したものの積が，解となることを利用したくなると思う．
それを実行しようとすると，今回の問題の制約的に素朴な素数判定法を利用した素因数分解をおこなう必要があるが，一つの整数の素因数分解に O(√N)=10^(9) かかってしまい，間に合わない．
そこで，ユークリッドの互除法を利用する．つまり，N個の整数の(G,C,D)は gcd(a1,gcd(a2,gcd(a3,gcd(...)))) となることを利用すればよい．
最悪計算量は O(N*log2(max(Ai)))<10^(7) となり，高速．
'''
def gcd(a,b)->int:
    if b==0:
        return a
    return gcd(b,a%b)

n=int(input())
a=list(map(int,input().split()))

ans=a[0]
for i in range(1,len(a)):
    ans=gcd(ans,a[i])
print(ans)