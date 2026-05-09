'''アルゴリズムと工夫点(Primality Test/CPU: 60 ms Memory: 80852 KB  Length: 284 B)
素数の素朴な判定法で解ける．
詳しくは先週の「AlMath_011.py」を参照のこと．
'''
def isPrime(x)->bool:
    if x==2:
        return True
    if x%2==0 or x<=1:
        return False
    i=3
    while i*i<=x:
        if x%i==0:
            return False
        i+=2
    return True

n=int(input())
if isPrime(n):
    print("Yes")
else :
    print("No")