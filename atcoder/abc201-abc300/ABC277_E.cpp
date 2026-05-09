/*アルゴリズムと工夫点(Crystal Switches/CPU: 160 ms Memory: 28244 KB  Length: 1817 B)
高橋君の状態sをs={0,1}で定義し，スイッチを押すとその状態が反転するとし，辺それぞれにも状態sを付与すれば，高橋君と辺の状態が一致するときに限り，その辺を渡ることができる．
そこで，頂点の数を状態sの個数分増やす．すると，visited[s][i]=(状態sの時の頂点iに到達するのにかかる移動の最小回数) とするテーブルを管理したBFSを行うことで，解を求めることができる．
最悪計算量はO(N+M)<10^6 となり，高速．
※初見5完達成!嬉しい!
※解説では，スイッチを押す作業を状態sの異なる同じ頂点にコスト0で移動すると考えた「0-1BFS」で解いている．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,bool> p;

int n,m,k;

int main(){
    int i,j,ii;
    scanf("%d%d%d",&n,&m,&k);
    vector<vector<p> > adj(n,vector<p>(0));
    while(m--){
        scanf("%d%d%d",&i,&j,&ii);
        i--;j--;
        adj[i].push_back(p(j,ii));
        adj[j].push_back(p(i,ii));
    }
    vector<bool> isSwitch(n,false);
    rep(i,k){
        scanf("%d",&j);
        isSwitch[j-1]=true;
    }
    auto bfs=[&]()->int{
        int i,j;
        const int INF=(int)(1e9);
        vector<vector<int> > visited(n,vector<int>(2,INF));
        queue<p> que;
        p now;
        que.push(p(0,true));
        visited[0][true]=0;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now.first].size()){
                if(now.second==adj[now.first][i].second&&visited[adj[now.first][i].first][now.second]==INF){
                    visited[adj[now.first][i].first][now.second]=visited[now.first][now.second]+1;
                    que.push(p(adj[now.first][i].first,now.second));
                }
            }
            if(isSwitch[now.first]){
                rep(i,adj[now.first].size()){
                    if(now.second!=adj[now.first][i].second&&visited[adj[now.first][i].first][!now.second]==INF){
                        visited[adj[now.first][i].first][!now.second]=visited[now.first][now.second]+1;
                        que.push(p(adj[now.first][i].first,!now.second));
                    }
                }
            }
        }
        return (i=min(visited[n-1][0],visited[n-1][1]))==INF?-1:i;
    };
    printf("%d\n",bfs());
    return 0;
}