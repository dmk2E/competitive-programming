/*アルゴリズムと工夫点(Medicines on Grid/CPU: 232 ms Memory: 16224 KB  Length: 3339 B)
スタート位置とゴール位置、薬がある位置それぞれの間の距離が分かれば、それらを頂点とする重み付き無効グラフGに置き換えることができる(それ以外の位置の情報を省略できる)。したがって、Gを表現する隣接リストadjを各頂点を始点
とするbfsを行って作成する前処理を行う。この最悪計算量はO(H*W*N)となる。その後にG上でbfsを行って解を判定する。この際、状態をとり得るエネルギーの値分だけ拡張しておくこと。このbfsの最悪計算量はO(H*W*N)となる。
全体の最悪計算量はO(H*W*N)=200*200*300≒10^7 となり、高速に動作する。
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 300
#define MAX_H 200
#define MAX_W 200
#define MAX_E 40000
#define START 0
#define SPACE -1
#define NIL -2
#define MAX_D 4
using namespace std;

typedef pair<int,int> p;

typedef struct data{
    int now,e;

    data(int nnow=0,int ee=0):now(nnow),e(ee){}
}Data;

int h,w,n,r[MAX_N],c[MAX_N],e[MAX_N],mmap[MAX_H][MAX_W+1],adj[MAX_N+1][MAX_N+2];//e[i]:薬i-1のEの値

void bfs(int sy,int sx,int id){
    int i,j,dy[MAX_D]={-1,0,1,0},dx[MAX_D]={0,1,0,-1},visited[MAX_H][MAX_W];
    queue<p> que;
    p now;
    rep(i,h)rep(j,w)visited[i][j]=NIL;
    adj[id][id]=0;
    if(mmap[sy][sx]>=1)
        adj[id][mmap[sy][sx]]=0;
    visited[sy][sx]=0;
    que.push(p(sy,sx));
    while(que.size()){
        now=que.front();que.pop();
        if(mmap[now.first][now.second]>=1)
            adj[id][mmap[now.first][now.second]]=visited[now.first][now.second];
        rep(i,MAX_D){
            if(now.first+dy[i]>=0&&now.first+dy[i]<h&&now.second+dx[i]>=0&&now.second+dx[i]<w&&mmap[now.first+dy[i]][now.second+dx[i]]!=NIL&&visited[now.first+dy[i]][now.second+dx[i]]==NIL){
                visited[now.first+dy[i]][now.second+dx[i]]=visited[now.first][now.second]+1;
                que.push(p(now.first+dy[i],now.second+dx[i]));
            }
        }
    }
}

bool bbfs(){
    int i;
    Data now;
    queue<Data> que;
    bool visited[MAX_N+2][MAX_E+1]={0};
    visited[0][0]=true;
    que.push(Data(0,0));
    while(que.size()){
        now=que.front();que.pop();
        //printf("Now:(%d,%d)\n",now.now,now.e);
        if(now.now==n+1)
            return true;
        rep(i,n+2){
            if(adj[now.now][i]!=NIL&&now.e>=adj[now.now][i]&&visited[i][now.e-adj[now.now][i]]==false){
                visited[i][now.e-adj[now.now][i]]=true;
                que.push(Data(i,now.e-adj[now.now][i]));
                //printf("New:(%d,%d)\n",i,now.e-adj[now.now][i]);
            }
        }
        if(now.now>0&&visited[now.now][e[now.now-1]]==false){
            visited[now.now][e[now.now-1]]=true;
            que.push(Data(now.now,e[now.now-1]));
            //printf("New:(%d,%d)\n",now.now,e[now.now-1]);
        }
    }
    return false;
}

int main(){
    int i,j,sy,sx,gy,gx;
    char cc;
    scanf("%d%d",&h,&w);
    rep(i,h){
        getchar();
        rep(j,w){
            cc=getchar();
            if(cc=='.')
                mmap[i][j]=SPACE;
            else if(cc=='#')
                mmap[i][j]=NIL;
            else if(cc=='S'){
                sy=i;
                sx=j;
                mmap[i][j]=START;
            }else if(cc=='T'){
                gy=i;
                gx=j;
            }
        }
    }
    scanf("%d",&n);
    rep(i,n){
        scanf("%d%d%d",&r[i],&c[i],&e[i]);
        r[i]--;c[i]--;
        mmap[r[i]][c[i]]=i+1;
    }
    mmap[gy][gx]=n+1;//ゴールは「n+1」
    //rep(i,h){rep(j,w)printf("%2d ",mmap[i][j]);puts("");}
    rep(i,n+1)rep(j,n+2)adj[i][j]=NIL;
    rep(i,n+1){
        if(i==0)
            bfs(sy,sx,i);
        else
            bfs(r[i-1],c[i-1],i);
    }
    //rep(i,n+1){rep(j,n+2)printf("%2d ",adj[i][j]);puts("");}
    printf("%s\n",bbfs()?"Yes":"No");
    return 0;
}