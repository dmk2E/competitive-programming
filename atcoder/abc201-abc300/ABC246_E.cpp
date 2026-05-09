/*アルゴリズムと工夫点(Bishop 2/CPU: 693 ms Memory: 167484 KB  Length: 1670 B)
通常のBFSを行うと，一つの頂点が持つ辺の数がNとなり，辺の総数がN^3 程になってしまうためTLEしてしまう．
そこで，1手の移動を，前回と同じ方向なら重みが0，そうでないなら重みが1となるグラフを考える．
するとこれは01-BFSの問題となる．
最悪計算量は O(N^(2))<10^7 となり高速．
※移動量が異なるが，コストが同じ->辺の張り方を工夫して，コストが同じ移動をする際には重み0の辺を貼るようなグラフを考える．
*/
#include<iostream>
#include<vector>
#include<deque>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int y,x,d;

    Data(int yy=0,int xx=0,int dd=0):y(yy),x(xx),d(dd){};
};

int n,sy,sx,ey,ex;

int main(){
    int i,j;
    scanf("%d%d%d%d%d",&n,&sy,&sx,&ey,&ex);
    sy--;sx--;ey--;ex--;
    vector<vector<bool> > mmap(n,vector<bool>(n));
    rep(i,n){
        getchar();
        rep(j,n)mmap[i][j]=getchar()=='.';
    }
    auto bfs=[&](int sy,int sx,int ey,int ex)->int{
        int i,y,x;
        Data now;
        deque<Data> deq;
        const int NIL=(int)(1e9),dy[]={1,1,-1,-1},dx[]={1,-1,1,-1},MAX_D=4;
        vector<vector<vector<int> > > vis(n,vector<vector<int> >(n,vector<int>(MAX_D,NIL)));
        rep(i,MAX_D){
            vis[sy][sx][i]=1;
            deq.push_back(Data(sy,sx,i));
        }
        while(deq.size()){
            now=deq.front();deq.pop_front();
            rep(i,MAX_D){
                sy=now.y+dy[i];
                sx=now.x+dx[i];
                if(0<=sy&&sy<n&&0<=sx&&sx<n&&mmap[sy][sx]&&vis[now.y][now.x][now.d]+(now.d!=i)<vis[sy][sx][i]){
                    vis[sy][sx][i]=vis[now.y][now.x][now.d]+(now.d!=i);
                    if(now.d==i)
                        deq.push_front(Data(sy,sx,i));
                    else
                        deq.push_back(Data(sy,sx,i));
                }
            }
        }
        y=NIL;
        rep(i,MAX_D)y=min(y,vis[ey][ex][i]);
        return y==NIL?-1:y;
    };
    printf("%d\n",bfs(sy,sx,ey,ex));
    return 0;
}