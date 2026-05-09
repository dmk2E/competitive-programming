'''アルゴリズムと工夫点(88888888/CPU: 58 ms Memory: 76784 KB  Length: 334 B)
最悪計算量は O(log2(N))

勧誘チラシに書いた方が良いと思う事柄
・計算量の話
・メモリの話
・式変形結果
・和差積商の余りの話（逆元についても）
・高速なa^(b) 計算方法（繰り返し自乗法）
'''
MOD=998244353
def power(a:int,b:int)->int:
    tmp=a
    ans=1
    while b>0:
        if b & 1:
            ans=(ans*tmp)%MOD
        b>>=1
        tmp=(tmp*tmp)%MOD
    return ans

n=int(input())
n_length=len(str(n))

print(((n%MOD)*((power(10,n_length*n)-1+MOD)%MOD)*power(((power(10,n_length)-1+MOD)%MOD),MOD-2))%MOD)