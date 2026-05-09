'''アルゴリズムと工夫点(Recurrence Formula 2/CPU: 65 ms Memory: 81504 KB  Length: 1190 B)
(a[n],a[n-1],a[n-2])=((1,1,1),(1,0,0),(0,1,0))*(a[n-1],a[n-2],a[n-3])
                    =...
                    =((1,1,1),(1,0,0),(0,1,0))^(n-3)*(2,1,1)
を元に今まで通り行列累乗を行えばよい．
'''
MOD=1000000007

class Matrix:
    def __init__(self,array:list[list[int]]):
        len_y=len(array)
        len_x=len(array[0])
        self.array=[[array[y][x] for x in range(0,len_x)] for y in range(0,len_y)]
    
    def __mul__(self,other): #*演算子オーバーロード
        len_y=len(self.array)
        len_x=len(other.array[0])
        len_tmp=len(self.array[0])
        dst=[[0 for _ in range(0,len_x)] for _ in range(0,len_y)]
        for y in range(0,len_y):
            for x in range(0,len_x):
                for i in range(0,len_tmp):
                    dst[y][x]=(dst[y][x]+((self.array[y][i]%MOD)*(other.array[i][x]%MOD))%MOD)%MOD
        return Matrix(dst)
    
    def __getitem__(self,index):
        return self.array[index]

def power(mat:Matrix,a:int)->Matrix: #[]演算子オーバーロード
    length=len(mat.array)
    ans=Matrix([[0]*y+[1]+[0]*(length-y-1) for y in range(0,length)])
    while a>0:
        if a & 1:
            ans*=mat
        a>>=1
        mat*=mat
    return ans

n=int(input())
mat=Matrix([[1,1,1],[1,0,0],[0,1,0]])

mat=power(mat,n-3)
print(((mat[0][0]*2)%MOD+mat[0][1]%MOD+mat[0][2]%MOD)%MOD)