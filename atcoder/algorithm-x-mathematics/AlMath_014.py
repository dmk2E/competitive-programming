'''アルゴリズムと工夫点(Factorization/CPU: 61 ms Memory: 80908 KB  Length: 622 B)
詳細な説明は公式解説に任せる．
Nを素因数分解した時，√N以下の素数は高々1個しかないため，2<=x<=√N の範囲の素数で割れるだけ割ればよい．実際の処理では，2,3,5,7,9,...の順に割り切れる値xがあれば，xで割り切れなくなるまで割り続ければよい．
この割る回数だが，割る対象がNの時，logx(N) となる．よって最悪計算量はO(√N*log(N))≒10^7 より小さくなるため，高速．
'''
def primeFac(x):
    xx=x
    cnt=0
    ans=[]
    if xx%2==0:
        cnt=0
        while xx%2==0:
            cnt+=1
            xx//=2
        ans.append((2,cnt))
    i=3
    while i*i<=x:
        if xx%i==0:
            cnt=0
            while xx%i==0:
                cnt+=1
                xx//=i
            ans.append((i,cnt))
        i+=2
    if xx>1:
        ans.append((xx,1))
    return ans

n=int(input())
pF=primeFac(n)
ans=[]
for p,cnt in pF:
    while cnt>0:
        cnt-=1
        ans.append(p)
for i in range(0,len(ans)-1):
    print(ans[i],end=" ")
print(ans[len(ans)-1])