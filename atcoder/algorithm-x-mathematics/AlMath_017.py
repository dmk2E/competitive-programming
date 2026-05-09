'''アルゴリズムと工夫点(Least Common Multiple of N Integers/CPU: 72 ms Memory: 95596 KB  Length: 259 B)
N個の整数の最小公倍数は，lcm(a1,lcm(a2,lcm(a3,lcm(...)))) となることを利用すればよい．
gcd(a,b)*lcm(a,b)=a*b を満たすことより，lcm(a,b)を間接に求めればよい．
最悪計算量はO(N*log2(max(Ai)))<10^(7) より高速．
'''
def gcd(a,b)->int:
    if b==0:
        return a
    return gcd(b,a%b)

def lcm(a,b)->int:
    return (a//gcd(a,b))*b

n=int(input())
a=list(map(int,input().split()))

ans=lcm(a[0],a[1])
for i in range(2,len(a)):
    ans=lcm(ans,a[i])
print(ans)