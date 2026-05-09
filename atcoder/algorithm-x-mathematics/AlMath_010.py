'''アルゴリズムと工夫点(Factorial/CPU: 56 ms Memory: 76748 KB  Length: 69 B)
pythonの整数型は多倍数整数のため，オーバーフローを恐れなくて良いのは，C系やJavaに無い利点．
他言語では，long long型を使う等，オーバーフロー対策を行うこと．
最悪計算量はO(N)
'''
n=int(input())
ans=1
for i in range(1,n+1):
    ans*=i
print(ans)