'''アルゴリズムと工夫点(Domino Tiling/CPU: 80 ms Memory: 81952 KB  Length: 2208 B)
詳細は解説を参照してください．
※K=2を考えた時点でDPなのは読めたが，それ以降が分からなかった...
※難しすぎるため，飛ばしても大丈夫です．
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

k,n=map(int,input().split())

if k==2:
    li=[[0,0,0,1],
         [0,0,1,0],
         [0,1,0,0],
         [1,0,0,1]]
elif k==3:
    li=[[0,0,0,0,0,0,0,1],
         [0,0,0,0,0,0,1,0],
         [0,0,0,0,0,1,0,0],
         [0,0,0,0,1,0,0,1],
         [0,0,0,1,0,0,0,0],
         [0,0,1,0,0,0,0,0],
         [0,1,0,0,0,0,0,1],
         [1,0,0,1,0,0,1,0]]
else:
    li=[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
         [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0],
         [0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0],
         [0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1],
         [0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
         [0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
         [0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1],
         [0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0],
         [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
         [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0],
         [0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0],
         [0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1],
         [0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0],
         [0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0],
         [1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1]]


mat=power(Matrix(li),n)
print(mat[(1<<k)-1][(1<<k)-1])