/*アルゴリズムと工夫点(Round Trip/CPU: 12 ms Memory: 4572 KB  Length: 1702 B)
各マスを頂点とし，4方向に隣接する，互いに行き来可能な頂点同士を辺で繋いだ重み無し無向グラフ上で，'S'の頂点を含む閉路が存在するか判定すればよい．
これは，BFSで実装することができ，最悪計算量はO(4*4*H*W)≒10^7 となり高速．
※初見5完達成!
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int h,w,sy,sx;

int main(){
    int i,j;
    char tmp;
    scanf("%d%d",&h,&w);
    vector<vector<bool> > c(h,vector<bool>(w,false));
    const int MAX_D=4,dy[]={-1,0,1,0},dx[]={0,1,0,-1};
    rep(i,h){
        getchar();
        rep(j,w){
            tmp=getchar();
            c[i][j]=tmp=='#'?false:true;
            if(tmp=='S'){
                sy=i;sx=j;
            }
        }
    }
    vector<vector<bool> > visited(h,vector<bool>(w,false));
    auto bfs=[&](int d)->bool{
        int i,y,x;
        p now;
        queue<p> que;
        if(0<=sy+dy[d]&&sy+dy[d]<h&&0<=sx+dx[d]&&sx+dx[d]<w&&c[sy+dy[d]][sx+dx[d]]){
            que.push(p(sy+dy[d],sx+dx[d]));
            visited[sy+dy[d]][sx+dx[d]]=true;
        }else
            return false;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=now.first+dy[i];x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&c[y][x]&&!visited[y][x]){
                    if(y==sy&&x==sx){
                        if(d==((MAX_D+i-2)%MAX_D))continue;
                        //printf("(%d,%d)\n",now.first,now.second);printf("%d->%d\n",d,i);
                        return true;
                    }
                    que.push(p(y,x));
                    visited[y][x]=true;
                }
            }
        }
        return false;
    };
    rep(i,MAX_D)if(bfs(i))break;
    printf("%s\n",i==MAX_D?"No":"Yes");
    return 0;
}