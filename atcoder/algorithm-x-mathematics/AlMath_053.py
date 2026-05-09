'''アルゴリズムと工夫点(Sum of 4^N/CPU: 58 ms Memory: 76728 KB  Length: 258 B)
高校数学Bで習った，等比級数の和の公式を用いると，4^(0)+4^(1)+4^(2)+...+4^(N)=1*(4^(N+1)-1)/(4-1)=(4^(N+1)-1)/3
となるから，この値をMODで割った余りを用いればよい．
最悪計算量は O(log2(N))<10^2 となり十分高速．
'''
MOD=1000000007
def power(a:int,b:int)->int:
    if b==0:
        return 1
    res=power(((a%MOD)*(a%MOD))%MOD,b//2)
    if b%2==1:
        res=(res*(a%MOD))
    return res%MOD

n=int(input())

print((((power(4,n+1)-1+MOD)%MOD)*power(3,MOD-2))%MOD)