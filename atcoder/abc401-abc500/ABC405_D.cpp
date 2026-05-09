/*アルゴリズムと工夫点(Escape Route/CPU: 44 ms Memory: 17448 KB  Length: 1362 B)
非常口全てを始点とする多始点BFSで各通路マスへの最短経路を求め，その時にどの方向から来たのかを同時に記録しておけばよい．
出力の際は，その反対方向を書き込む．
最悪計算量は，O(H*W)<10^7 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<P> es;
    vector<string> mp(h);
    rep(i,h)cin>>mp[i];  
    rep(i,h)rep(j,w){
        if(mp[i][j]=='E')es.push_back(P(i,j));
    }
    const int dy[]={-1,0,1,0},MAX_D=4;
    const int dx[]={0,1,0,-1},NIL=-1;
    const char alf[]="^>v<";
    auto bfs=[&]()->void{
        int i,j;
        P now;
        queue<P> que;
        vector<vector<int> > vis(h,vector<int>(w,NIL));
        rep(i,es.size()){
            que.push(es[i]);
            vis[es[i].first][es[i].second]=0;
        }
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                int y,x;
                y=now.first+dy[i];
                x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&vis[y][x]==NIL&&mp[y][x]=='.'){
                    vis[y][x]=i;
                    que.push(P(y,x));
                }
            }
        }
        rep(i,h)rep(j,w){
            if(mp[i][j]=='.')mp[i][j]=alf[(vis[i][j]+2)%MAX_D];
        }
    };
    bfs();
    rep(i,h)cout<<mp[i]<<endl;
    return 0;
}