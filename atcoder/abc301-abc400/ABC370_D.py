'''アルゴリズムと工夫点(Cross Explosion/CPU: 1251 ms Memory: 415964 KB  Length: 3605 B)
pythonにおけるクラス変数は，全てのインスタンスで共有されてしまう．
そのため，コンストラクタで毎回宣言&初期化する必要がある．
'''
class UnionFind:
    def __init__(self,n):
        self.m_par=[]
        self.m_rank=[]
        self.m_min=[]
        self.m_max=[]
        for i in range(0,n):
            self.m_par.append(i)
            self.m_rank.append(0)
            self.m_min.append(i)
            self.m_max.append(i)
    def root(self,x):
        if self.m_par[x]==x:
            return x
        self.m_par[x]=self.root(self.m_par[x])
        return self.m_par[x]
    def unite(self,x,y):
        x=self.root(x)
        y=self.root(y)
        if x==y:
            return 
        if self.m_rank[x]<self.m_rank[y]:
            self.m_par[x]=y
            self.m_min[y]=min(self.m_min[x],self.m_min[y])
            self.m_max[y]=max(self.m_max[x],self.m_max[y])
        else:
            self.m_par[y]=x
            self.m_min[x]=min(self.m_min[x],self.m_min[y])
            self.m_max[x]=max(self.m_max[x],self.m_max[y])
            if self.m_rank[x]==self.m_rank[y]:
                self.m_rank[y]+=1
    def isSame(self,x,y):
        self.root(x)==self.root(y)
    
h,w,q=map(int,input().split())
cnt=0
row=[]
col=[]
isWall=[]
for i in range(0,h):
    row.append(UnionFind(w))
    isWall.append([True for _ in range(0,w)])
for j in range(0,w):
    col.append(UnionFind(h))

dy=[-1,0,1,0]
dx=[0,1,0,-1]
while q>0:
    q-=1
    r,c=map(int,input().split())
    r-=1;c-=1
    if isWall[r][c] :
        cnt+=1
        isWall[r][c]=False
        for i in range(0,len(dy)):
            rr=r+dy[i]
            cc=c+dx[i]
            if rr>=0 and rr<h and cc>=0 and cc<w and isWall[rr][cc]==False:
                row[rr].unite(c,cc)
                col[cc].unite(r,rr)
    else :
        #print("start")
        tmp=col[c].root(r)
        minY=col[c].m_min[tmp]
        maxY=col[c].m_max[tmp]
        #print(f"minY:{minY} maxY:{maxY}")
        tmp=row[r].root(c)
        minX=row[r].m_min[tmp]
        maxX=row[r].m_max[tmp]
        #print(f"minX:{minX} maxX:{maxX}")
        if minY-1>=0 :
            if isWall[minY-1][c]:
                cnt+=1
                isWall[minY-1][c]=False
                y=minY-1
                x=c
                for i in range(0,len(dy)):
                    rr=y+dy[i]
                    cc=x+dx[i]
                    if rr>=0 and rr<h and cc>=0 and cc<w and isWall[rr][cc]==False:
                        row[y].unite(x,cc)
                        col[x].unite(y,rr)
        if maxY+1<h :
            cnt+=1
            isWall[maxY+1][c]=False
            y=maxY+1
            x=c
            for i in range(0,len(dy)):
                rr=y+dy[i]
                cc=x+dx[i]
                if rr>=0 and rr<h and cc>=0 and cc<w and isWall[rr][cc]==False:
                    row[y].unite(x,cc)
                    col[x].unite(y,rr)
        if minX-1>=0 :
            cnt+=1
            isWall[r][minX-1]=False
            y=r
            x=minX-1
            for i in range(0,len(dy)):
                rr=y+dy[i]
                cc=x+dx[i]
                if rr>=0 and rr<h and cc>=0 and cc<w and isWall[rr][cc]==False:
                    row[y].unite(x,cc)
                    col[x].unite(y,rr)
        if maxX+1<w :
            cnt+=1
            isWall[r][maxX+1]=False
            y=r
            x=maxX+1
            for i in range(0,len(dy)):
                rr=y+dy[i]
                cc=x+dx[i]
                if rr>=0 and rr<h and cc>=0 and cc<w and isWall[rr][cc]==False:
                    row[y].unite(x,cc)
                    col[x].unite(y,rr)
print(h*w-cnt)