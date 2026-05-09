'''アルゴリズムと工夫点(Fibonacci Easy (mod 1000000007)/CPU: 123 ms Memory: 81108 KB  Length: 118 B)
漸化式の定義に従って，前2つの項の値を保持して，順番に項を求めていく．
'''
MOD=1000000007
n=int(input())
a1,a2=1,1
for i in range(3,n+1):
    ai=(a1+a2)%MOD
    a1=a2
    a2=ai
print(a2)