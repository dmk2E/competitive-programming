/*アルゴリズムと工夫点(Grid and Magnet/CPU: 812 ms Memory: 70180 KB  Length: 2162 B)
問題は、1回のBFSで塗りつぶせる領域の面積の最大値を求めよ、という問題にいいかえれる。ただし、内部の訪れたかのフラグに二次元配列を用いると、その初期化でTLEしてしまうことに注意。
最悪計算量はO(N+M)<10^7 となり、十分高速。
*/
#include<iostream>
#include<queue>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 1000
#define MAX_W 1000
#define MAX_D 4
#define FREE 2
#define MAGNET 1
#define VISITED 0
#define STOPPED -1
using namespace std;

typedef pair<int,int> p;

int h,w,state[MAX_H][MAX_W],dy[]={-1,0,1,0},dx[]={0,1,0,-1};

void show(){
    int i,j;
    rep(i,h){
        rep(j,w)
            printf("%2d ",state[i][j]);
        puts("");
    }
    puts("");
}

int bfs(int y,int x){
    //printf("start:%d %d\n",y,x);show();
    int cnt=1,i,j,yy,xx;
    map<p,bool> visited;
    p now;
    queue<p> que;
    now=p(y,x);
    rep(i,MAX_D){
        y=now.first+dy[i];x=now.second+dx[i];
        if(y>=0&&y<h&&x>=0&&x<w&&state[y][x]==MAGNET)
            break;
    }
    state[now.first][now.second]=i==MAX_D?VISITED:STOPPED;
    visited[now]=true;
    if(state[now.first][now.second]==VISITED)
        que.push(now);
    while(que.size()){
        now=que.front();que.pop();
        rep(i,MAX_D){
            y=now.first+dy[i];x=now.second+dx[i];
            if(y>=0&&y<h&&x>=0&&x<w&&visited[p(y,x)]==false&&(state[y][x]==FREE||state[y][x]==STOPPED)){
                cnt++;
                visited[p(y,x)]=true;
                if(state[y][x]==STOPPED)
                    continue;
                rep(j,MAX_D){
                    yy=y+dy[j];xx=x+dx[j];
                    if(yy>=0&&yy<h&&xx>=0&&xx<w&&state[yy][xx]==MAGNET)
                        break;
                }
                state[y][x]=j==MAX_D?VISITED:STOPPED;
                if(state[y][x]==VISITED)
                    que.push(p(y,x));
            }
        }
    }
    //show();printf("%d\n",cnt);
    return cnt;
}

int main(){
    int i,j,max=-1,k=-1;
    char c;
    scanf("%d%d",&h,&w);
    rep(i,h){
        getchar();
        rep(j,w){
            c=getchar();
            state[i][j]=c=='.'?FREE:MAGNET;
        }
    }
    rep(i,h){
        rep(j,w){
            if(state[i][j]==FREE&&(k=bfs(i,j))>max){
                max=k;
            }
        }
    }
    printf("%d\n",max);
    return 0;
}