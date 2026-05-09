'''アルゴリズムと工夫点(Number of Multiples 1/CPU: 58 ms Memory: 76776 KB  Length: 153 B)
今回は制約的に，愚直に全探索しても良いが，数学の知識があれば高速化できる．
高校数学Aの集合(包除原理)を利用すれば，O(log2(y))で解くことが可能．
まずx,yの最大公約数(G,C,M)は，ユークリッドの互除法でO(log2(y))で求めることができる．
x*y=(G,C,M)*(L,C,M)となることから間接的に最小公倍数(L,C,M)を求めることができる．
すると，求める値は (1~Nの中でXの倍数の数)+(1~Nの中でYの倍数の数)-(1~Nの中で(L,C,M)の倍数の数) となり，高速に求めることができる．
「1000000000000000000 1236 22352」のような入力でも，高速に求めることができる．
※ユークリッドの互除法は，参考書の3章に載っているので，気になる方はそちらを参照してください．
'''
n,x,y=map(int,input().split())

def gcd(a,b):
    if b==0:
        return a
    return gcd(b,a%b)

lcm=x*y//gcd(x,y)
print(f"{n//x+n//y-n//lcm}")
# # O(N)解法(CPU: 61 ms Memory: 81068 KB  Length: 115 B)
# n,x,y=map(int,input().split())
# cnt=0
# for i in range(1,n+1):
#     if i%x==0 or i%y==0:
#         cnt+=1
# print(cnt)