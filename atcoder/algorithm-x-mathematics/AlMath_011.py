'''アルゴリズムと工夫点(Print Prime Numbers/CPU: 61 ms Memory: 81440 KB  Length: 467 B)
素数列挙の知識が無い人は，「N以下の整数全てで割り切れるか」で素数判定をしてしまうと思う．
今回は制約的にそれでも問題ないが，メジャーな素数列挙の方法は以下の2つがあり，本書の後半でより詳しく扱うが，簡単な説明をしておく．

素数列挙法には，<i>素朴な探索 <ii>エラトステネスの篩 の2つあり，それぞれ用途が異なり，どちらも使えることが望ましい．
<i>素朴な判定
ある整数Aが，A=a*b(0<a<=b) の形に変形できるとする(a<=bとしても一般性を失わないことに注意)．
すると，a^2=a*a<=a*b=A となり，a<=√A となる．
また，因数の値が最大になる時は，必ず因数の数が2個の時である．
よって，ある整数Aが素数かどうかは，「A=a*bの形に因数分解可能か」と同義であり，それを調べればよい．
最悪計算量はO(√A)

<ii>エラトステネスの篩
詳しくは
https://algo-method.com/descriptions/64

2つの使い分けについてだが，
・<i>は，ある一つの整数Aが素数化の判定にO(√N)かかる．従って，複数の整数の素数判定を行う際には適さない．
しかし，10^(13)くらい大きい数字に対しても，素数判定が可能．
・<ii>は前処理にO(A*log(log(A)))かかるが，A以下の整数全てに関してO(1)で素数か否か判定可能
しかし，10^(13)くらい大きい数字に対しては，素数判定が不可能(前処理でTLEしてしまう)．

今回は，計算量的にはエラトステネスの篩で解く方が高速．
最悪計算量はO(N*log(log(N)))≒10^3 となり，十分高速．
'''
#素朴な判定Ver:最悪計算量O(N*√N)≒10^(4.5)<10^5 で十分高速 (CPU: 70 ms Memory: 81840 KB)
# def isPrime(x)->bool:
#     if x==2:
#         return True
#     if x%2==0 or x<=1:
#         return False
#     i=3
#     while i*i<=x:
#         if x%i==0:
#             return False
#         i+=2
#     return True

# n=int(input())
# ans=[]
# for i in range(0,n+1):
#     if isPrime(i):
#         ans.append(i)
# for i in range(0,len(ans)-1):
#     print(f"{ans[i]}",end=" ")
# print(f"{ans[len(ans)-1]}")

#エラトステネスの篩Ver
def init(MAX_X)->list:
    isPrime=[True]*(MAX_X+1)
    isPrime[0]=isPrime[1]=False
    for i in range(2,MAX_X+1):
        if isPrime[i]:
            j=2*i
            while j<=MAX_X:
                isPrime[j]=False
                j+=i
    return isPrime

n=int(input())
isPrime=init(n)
ans=[]
for i in range(0,n+1):
    if isPrime[i]:
        ans.append(i)
for i in range(0,len(ans)-1):
    print(f"{ans[i]}",end=" ")
print(f"{ans[len(ans)-1]}")