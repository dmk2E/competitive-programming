'''アルゴリズムと工夫点(Fibonacci Hard (mod 1000000000) /CPU: 57 ms Memory: 76472 KB  Length: 750 B)
行列累乗で，O(log2(N))で解ける．
漸化式を行列の積の形で表せれば，高速に求めることができる．
※ 行列の累乗に関しては，自分も初見でした
2つの正方行列A,B に対して，行列の積 A*B=B*A は必ずしも成立しないが，結合法則（A*(B*C)=(A*B)*C）は成立する．
行列の積は，線形代数の授業を思い出すこと．
'''
MOD=1000000000

def mulMatrix(mat1:list[list[int]],mat2:list[list[int]])->list[list[int]]:
    mat=[[0 for _ in range(0,len(mat2[0]))] for i in range(0,len(mat1))]
    for i in range(0,len(mat)):
        for j in range(0,len(mat[i])):
            for k in range(0,len(mat[i])):
                mat[i][j]+=((mat1[i][k]%MOD)*(mat2[k][j]%MOD))%MOD
                mat[i][j]%=MOD
    return mat

def power(mat:list[list[int]],x:int)->int:
    ans=[[mat[i][j] for j in range(0,len(mat[i]))] for i in range(0,len(mat))]
    x-=1
    while x>0:
        if x&1:
            ans=mulMatrix(ans,mat)
        mat=mulMatrix(mat,mat)
        x>>=1
    return ans

n=int(input())

a=[[1,1],[1,0]]
a=power(a,n-1)
print((a[1][0]+a[1][1])%MOD)