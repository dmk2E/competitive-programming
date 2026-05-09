'''アルゴリズムと工夫点(Sum of Divisors/CPU: 1354 ms Memory: 159676 KB  Length: 204 B)
f(k)の値をまず求める．これは，1~Nまでの整数それぞれで，1~Nまでの全ての整数それぞれが割り切れるか記録すればよい．
ここで，ある整数aで，1~Nの整数が割り切れるか確かめる際，見るべき整数の数はN/aとなる．
よって，最悪計算量は，O(N/1+N/2+N/3+...+N/N+N)=O(N(1/1+1/2+1/3...+1/N)+N)=O(N*log2(N))≒10^8 となり間に合う．
※"1/1+1/2+...+1/N"は調和級数と呼ばれ，log2(N)で近似できる．
※pythonだとギリギリの計算量である．
'''
n=int(input())
cnt_div=[0 for _ in range(0,n+1)]
for i in range(1,n+1):
    j=i
    while j<=n:
        cnt_div[j]+=1
        j+=i

ans=0
for k in range(1,n+1):
    ans+=k*cnt_div[k]
print(ans)