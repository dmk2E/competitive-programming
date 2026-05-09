'''アルゴリズムと工夫点(Power/CPU: 58 ms Memory: 76612 KB  Length: 223 B)
a^bは，繰り返し自乗法を用いれば，最悪計算量O(log2(b)) で高速に求めることができる．
実装は再帰を用いているが，参考書のように単純なループで書く方法もあるので，お好みで．
'''
MOD=1000000007
def power(a:int,b:int)->int:
    if b==0:
        return 1
    res=power((a%MOD)*(a%MOD),b//2)
    if b%2==1:
        res=res*(a%MOD)
    return res%MOD
a,b=map(int,input().split())
print(power(a,b))