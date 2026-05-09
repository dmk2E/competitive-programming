'''アルゴリズムと工夫点(Combination Hard/CPU: 69 ms Memory: 96680 KB  Length: 502 B)
解は，(X+Y)!/(X!*Y!) % MOD となる．
逆元を用いれば，商について余りの計算が可能になるから，0!~(X+Y)!の逆元を前処理で求めておく．
1/N! ≡(1/(N+1)!)*(N+1) となることを利用し，(X+Y)!の逆元に順に(X+Y),(X+Y-1),...を掛けていけば，高速化できる．
最悪計算量は O(X+Y+log2(X+Y))<10^6 となり十分高速．
※逆元（モジュラ逆数）の説明は参考書を熟読すること!
※ mod M における割り算を定義するにあたり重要なのは，a*b≡c (mod M) であるならば，a≡c/b(=c*(1/b)) を満たす必要があるということ
'''
MOD=1000000007
def power(a:int,b:int)->int:
    if b==0:
        return 1
    res=power(((a%MOD)*(a%MOD))%MOD,b//2)
    if b%2==1:
        res=res*(a%MOD)
    return res%MOD

x,y=map(int,input().split())

fac=[1]
for i in range(0,x+y):
    fac.append(((fac[i]%MOD)*((i+1)%MOD))%MOD)

inv_fac=[0 for _ in range(0,x+y+1)]
inv_fac[x+y]=power(fac[x+y],MOD-2)
for i in range(x+y-1,-1,-1):
    inv_fac[i]=(inv_fac[i+1]*((i+1)%MOD))%MOD

print((((fac[x+y]*inv_fac[x])%MOD)*inv_fac[y])%MOD)