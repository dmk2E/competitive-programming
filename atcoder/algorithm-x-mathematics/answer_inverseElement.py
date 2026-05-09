'''アルゴリズムと工夫点(逆元体験プログラム/CPU: - ms Memory: - KB  Length: - B)
入力:
P Q
出力:
P/Q(mod MOD) (MODは"素数")

のようなプログラムを作成した．
-アルゴリズムの簡易概要-
・前置き
ある2数x,yの和・差・積の結果をMODで割った余りは，x%MOD,y%MODそれぞれに対して和・差・積を行った結果をMODで割った余りと一致する．
しかし，商についてはそうはいかず，逆元を考える必要がある

・アルゴリズム
フェルマーの小定理: x^(p-1)≡1(mod p(=素数)) より，x*x^(p-2)≡1(mod p(=素数)) と式変形できる．
したがって，mod pの世界における(1/x)の値，つまりxの逆元は，x^(p-2) となる．
よって，出力の値を求めるには，pの値に「qの逆元」をかければよい．
※ただし，この方法が通用するのは，MODが素数の時のみであることに注意

MOD=7の場合，2の逆元は，2^(5)=32 
よって，以下mod7 とすると，
12/2≡12*32≡(12%7)*(32%7)≡5*4≡20≡(20%7)≡6
と正しく計算できる．
同様に，
11/2≡11*32≡4*4≡16≡2
と表される．
'''
MOD=7
# MOD=998244353

#繰り返し自乗法で，x^aを，O(log2(a))で計算
def power(x:int,a:int)->int:
    if a==0:
        return 1
    res=power(((x%MOD)*(x%MOD))%MOD,a//2)
    if a%2==1:
        res=res*x
    return res%MOD

#powerお試し    
# while True:
#     x,a=map(int,input().split())
#     print(power(x,a))

while True:
    print("Input the number P,Q",end=":")
    p,q=map(int,input().split())
    if p<0 or q<=0:
        break
    print((p*power(q,MOD-2))%MOD)
print("This program is over.")