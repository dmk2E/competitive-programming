/*アルゴリズムと工夫点(Maze Challenge with Lack of Sleep/CPU: 264 ms Memory: 83580 KB  Length: 1488 B)
そのマスに移動した際のあり得る状態は，4方向のうちどの方向で移動したかの4パターンであるから，各マスの状態を4つに増やして拡張ダイクストラ法で解く．
※今回は，距離の最小を求めるのではなく，方向転換の回数であり，移動毎にかかるコストは一定ではないから，BFSでは解けない．
※公式解説では，拡張BFS(01-BFS)というもので解ける模様．これは，辺の重みが0と1しかない場合に用いることができる手法．
ダイクストラ法の亜種であり，重みが0の方を通る場合は先頭にその情報を追加，1の方を通る場合はその情報を末端に追加する両端キュー(deque)を用いる．計算量はO(V+E)となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<deque>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 1000
#define MAX_W 1000
#define MAX_D 4
#define NIL -1
#define INF (int)(1e7)
using namespace std;

typedef pair<int,int> p;

int h,w,sy,sx,gy,gx;
bool mmap[MAX_H][MAX_W];

int bfs(int y,int x){
    int i,d;
    const int dy[]={0,1,0,-1},dx[]={1,0,-1,0};
    vector<vector<vector<int> > > visited(h,vector<vector<int> >(w,vector<int>(MAX_D,INF)));
    deque<p> deq;
    p tmp;
    rep(i,MAX_D){
        deq.push_front(p(y*w+x,i));
        visited[y][x][i]=0;
    }
    while(deq.size()){
        y=deq.front().first/w;x=deq.front().first%w;d=deq.front().second;deq.pop_front();
        if(y==gy&&x==gx)return visited[y][x][d];
        rep(i,MAX_D){
            if(0<=y+dy[i]&&y+dy[i]<h&&0<=x+dx[i]&&x+dx[i]<w&&mmap[y+dy[i]][x+dx[i]]&&visited[y][x][d]+(d!=i)<visited[y+dy[i]][x+dx[i]][i]){
                visited[y+dy[i]][x+dx[i]][i]=visited[y][x][d]+(d!=i);
                if(d!=i)
                    deq.push_back(p((y+dy[i])*w+x+dx[i],i));
                else
                    deq.push_front(p((y+dy[i])*w+x+dx[i],i));
            }
        }
    }
    return NIL;
}

int main(){
    int i,j;
    char c;
    scanf("%d%d%d%d%d%d",&h,&w,&sy,&sx,&gy,&gx);
    sy--;sx--;gy--;gx--;
    rep(i,h){
        getchar();
        rep(j,w)
            mmap[i][j]=getchar()=='.';
    }
    printf("%d\n",bfs(sy,sx));
    return 0;
}
/*CPU: 1997 ms Memory: 140268 KB  Length: 1641 B
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 1000
#define MAX_W 1000
#define MAX_D 4
#define NIL -1
using namespace std;

typedef struct data{
    int y,x,d,cost;

    data(int yy=NIL,int xx=NIL,int dd=NIL,int ccost=NIL):y(yy),x(xx),d(dd),cost(ccost){}

    bool operator<(const data& k)const{
        return cost<k.cost;
    }
}Data;

int h,w,sy,sx,gy,gx;
bool mmap[MAX_H][MAX_W];

int dijk(int sy,int sx){
    int i,dy[]={0,1,0,-1},dx[]={1,0,-1,0};
    vector<vector<vector<bool> > > visited(h,vector<vector<bool> >(w,vector<bool>(MAX_D,false)));
    Data now,temp;
    priority_queue<Data> PQ;
    rep(i,MAX_D)
        PQ.push(Data(sy,sx,i,0));
    while(PQ.size()){
        do{
            now=PQ.top();PQ.pop();
        }while(visited[now.y][now.x][now.d]&&PQ.size());
        if(visited[now.y][now.x][now.d])break;
        //printf("(%d,%d,%d):%d\n",now.y,now.x,now.d,-now.cost);
        if(now.y==gy&&now.x==gx)return -now.cost;
        visited[now.y][now.x][now.d]=true;
        rep(i,MAX_D){
            if(0<=now.y+dy[i]&&now.y+dy[i]<h&&0<=now.x+dx[i]&&now.x+dx[i]<w&&mmap[now.y+dy[i]][now.x+dx[i]]&&visited[now.y+dy[i]][now.x+dx[i]][i]==false&&now.d!=(i+2)%MAX_D)
                PQ.push(Data(now.y+dy[i],now.x+dx[i],i,now.cost-(now.d!=i)));
        }
    }
    return NIL;
}

int main(){
    int i,j;
    char c;
    scanf("%d%d%d%d%d%d",&h,&w,&sy,&sx,&gy,&gx);
    sy--;sx--;gy--;gx--;
    rep(i,h){
        getchar();
        rep(j,w)
            mmap[i][j]=getchar()=='.';
    }
    printf("%d\n",dijk(sy,sx));
    return 0;
}
*/