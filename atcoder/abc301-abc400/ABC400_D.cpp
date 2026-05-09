/*アルゴリズムと工夫点(Takahashi the Wall Breaker/CPU: 92 ms Memory: 15860 KB  Length: 2425 B)
H*W個数の区間それぞれを頂点とし，上下左右1マス，または2マス先に重み1の辺を張った無向重み付きグラフ上で，0-1BFSを行えばよい．
最悪計算量は O(H*W+H*W*8)=O(H*W)<10^7 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<deque>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int h,w,a,b,c,d;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<vector<bool> > mmap(h,vector<bool>(w,false));
    rep(i,h){
        getchar();
        rep(j,w)mmap[i][j]=(getchar()=='#');
    }
    const int INF=h*w+1;
    const int dy[]={-1,0,1,0},MAX_D=4;
    const int dx[]={0,1,0,-1};
    auto bfs=[&](P now,P goal)->int{
        int i,y,x;
        deque<P> deq;
        vector<vector<int> > dist(h,vector<int>(w,INF));
        dist[now.first][now.second]=0;
        deq.push_back(now);
        while(deq.size()){
            now=deq.front();deq.pop_front();
            rep(i,MAX_D){
                y=now.first+dy[i];
                x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w){
                    if(mmap[y][x]){
                        if(dist[now.first][now.second]+1<dist[y][x]){
                            dist[y][x]=dist[now.first][now.second]+1;
                            deq.push_back(P(y,x));
                        }
                    }else{
                        if(dist[now.first][now.second]<dist[y][x]){
                            dist[y][x]=dist[now.first][now.second];
                            deq.push_front(P(y,x));
                        }
                    }
                    y=y+dy[i];
                    x=x+dx[i];
                    if(0<=y&&y<h&&0<=x&&x<w){
                        if(mmap[y][x]||mmap[y-dy[i]][x-dx[i]]){
                            if(dist[now.first][now.second]+1<dist[y][x]){
                                dist[y][x]=dist[now.first][now.second]+1;
                                deq.push_back(P(y,x));
                            }
                        }else{
                            if(dist[now.first][now.second]<dist[y][x]){
                                dist[y][x]=dist[now.first][now.second];
                                deq.push_front(P(y,x));
                            }
                        }   
                    }
                }
            }
        }
        return dist[goal.first][goal.second];
    };
    scanf("%d%d%d%d",&a,&b,&c,&d);
    printf("%d\n",bfs(P(a-1,b-1),P(c-1,d-1)));
    return 0;
}