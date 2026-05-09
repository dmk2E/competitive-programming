'''アルゴリズムと工夫点(Knight/CPU: 93 ms Memory: 134048 KB  Length: 636 B)
(i,j)から，(i+1,j+2)への移動をa回，(i+2,j+1)への移動をb回行うと，(a+2*b,2*a+b)の座標に移動する．
よって条件を満たす経路の存在するためには，
<i>a+2*b=X
<ii>2*a+b=Y
・a>=0,b>=0 a,bは共に整数
を満たす(a,b)が存在する必要がある．
<i>,<ii>の連立方程式を解いて，
・3*a=2*X-Y
・3*b=2*Y-X
だから，(2*X-Y,2*Y-X)が共に3の倍数かつ0以上の整数であれば，経路は存在する．
a,bの値が求まれば，解は (a+b)!/(a!*b!) となり，AlMath_051.py と同様の問題になる．
'''
import sys

MOD=1000000007
def power(a:int,b:int)->int:
    if b==0:
        return 1
    res=power(((a%MOD)*(a%MOD))%MOD,b//2)
    if b%2==1:
        res=res*(a%MOD)
    return res%MOD

x,y=map(int,input().split())

if (2*x-y)<0 or (2*y-x)<0 or (2*x-y)%3>0 or (2*y-x)%3>0:
    print(0)
    sys.exit()

a=(2*x-y)//3
b=(2*y-x)//3

fac=[1]
for i in range(0,a+b):
    fac.append(((fac[i]%MOD)*((i+1)%MOD))%MOD)

inv_fac=[0 for _ in range(0,a+b+1)]
inv_fac[a+b]=power(fac[a+b],MOD-2)
for i in range(a+b-1,-1,-1):
    inv_fac[i]=(inv_fac[i+1]*((i+1)%MOD))%MOD

print((((fac[a+b]*inv_fac[a])%MOD)*inv_fac[b])%MOD)