'''アルゴリズムと工夫点(Calculate GCD/CPU: 59 ms Memory: 76760 KB  Length: 120 B)
(a,b)の最大公約数は，ユークリッドの互除法を用いることで，O(log2(max(a,b)))と，高速で求めることができる．
「AlMath_007.py」で用いたように，様々な所で使えるので，覚えておこう(C++やpython(3.5以降)等，標準ライブラリで用意されている言語もある)．
'''
def gcd(a,b)->int:
    if b==0:
        return a
    return gcd(b,a%b)
a,b=map(int,input().split())
print(gcd(a,b))