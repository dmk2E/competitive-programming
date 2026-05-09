'''アルゴリズムと工夫点(Combination Easy/CPU: 57 ms Memory: 76716 KB  Length: 124 B)
pythonでは問題ないが，C言語等で解くときは，オーバーフローに注意．
※目安として覚えておくと良い，各整数型の最大値
・int型:32ビット整数 最大で，2^(31)-1≒2*10^9 
・long long 型:64ビット整数 最大で2^63-1≒9.2*10^18 
・unsigned long long 型:符号なし64ビット整数 最大で1.8*10^19 
'''
n,r=map(int,input().split())
fac=[1]
for i in range(0,n):
    fac.append(fac[i]*(i+1))
print((fac[n]//fac[r])//fac[n-r])