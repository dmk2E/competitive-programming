'''アルゴリズムと工夫点(幅優先探索/CPU: 79 ms Memory: 82032 KB  Length: 700 B)
幅優先探索の真骨頂は"最短経路探索"で，最短経路と聞いたらまずBFSを思い浮かべられるようになろう．
※移動にかかるコストが全て同一であればほぼほぼBFSで解ける．同一でない場合はダイクストラ法などで解く．
'''
from collections import deque
r,c=map(int,input().split())
sy,sx=map(int,input().split())
gy,gx=map(int,input().split())

dy=(-1,0,1,0)
dx=(0,1,0,-1)
MAX_D=4

mmap=[input() for _ in range(0,r)]

def bfs(sy:int,sx:int,gy:int,gx:int)->int:
    NIL=-1
    vis=[[NIL]*c for _ in range(0,r)]
    deq=deque()
    deq.append((sy,sx))
    vis[sy][sx]=0
    while len(deq)>0:
        sy,sx=deq.popleft()
        for i in range(0,MAX_D):
            y,x=sy+dy[i],sx+dx[i]
            if 0<=y and y<r and 0<=x and x<c and mmap[y][x]=='.' and vis[y][x]==NIL:
                deq.append((y,x))
                vis[y][x]=vis[sy][sx]+1
    return vis[gy][gx]
print(bfs(sy-1,sx-1,gy-1,gx-1))