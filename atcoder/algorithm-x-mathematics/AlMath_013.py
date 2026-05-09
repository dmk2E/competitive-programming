'''アルゴリズムと工夫点(Divisor Enumeration/CPU: 70 ms Memory: 80760 KB  Length: 380 B)
素数の素朴な判定法の応用で，約数列挙を行うことができる．
約数列挙の為には，N=a*b(a<=b)を満たす，(a,b)の組を全て列挙すればよい．
aさえ分かれば，ペアとなるbはb=n/aで求めることができるため，aさえ列挙できれば良い．
aとなりうる範囲は，a*a<=a*b=N より，1<=a<=√N であり，これらの値全てについてNを割り切れるか判定し，(a,b)を一つずる列挙すればよい．
aとbそれぞれ別の配列A,Bで保持して置けば，Aは昇順，Bは降順になっているため，上手く結合することで昇順に約数を格納することができる．
この処理にかかる最悪計算量は O(√N)<10^7 となり，高速．
'''
def x2Factors(x)->list:
    smaller=[]
    larger=[]
    i=1
    while i*i<=x:
        if x%i==0:
            smaller.append(i)
            if i<(x//i):
                larger.append(x//i)
        i+=1
    for i in range(0,len(larger)):
        smaller.append(larger[len(larger)-1-i])
    return smaller

n=int(input())
ans=x2Factors(n)
for x in ans:
    print(x)