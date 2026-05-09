/*アルゴリズムと工夫点(Hit and Away/CPU: 120 ms Memory: 28540 KB  Length: 1654 B)
始点を保持した多始点BFSで解く．
各危険な頂点について求める解は，(その頂点から最も近い安全な頂点までの距離)+(その頂点から2番目に近い安全な頂点までの距離) となる．
これは，安全な頂点全てを始点とする多始点BFSで解くことが出来る．
2番目に近い安全頂点までの距離も求める必要があるため，出発した始点も同時に管理して実装する．
最悪計算量は，O(N + M) < 10^7 （定数倍を考慮）となり高速．
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

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<vector<int> > adj(n);
    while(m--){
        int u,v;
        scanf("%d%d",&u,&v);
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    string s;
    cin >> s;
    const int NIL = -1;
    vector<vector<P> > dist(n,vector<P>(2,P(NIL,NIL)));// (dist, start)
    auto bfs = [&]()->void{
        int i;
        queue<P> que;
        rep(i,n)if(s[i] == 'S'){
            dist[i][0] = P(0,i);
            que.push(P(i,i)); // (now_vertex, start_vertex)
        }
        while(que.size()){
            auto [now_v, start_v] = que.front();que.pop();
            for(int nxt_v : adj[now_v]){
                if(dist[nxt_v][0].first == NIL){
                    int now_id = dist[now_v][0].second == start_v ? 0 : 1;
                    dist[nxt_v][0] = P(dist[now_v][now_id].first + 1, start_v);
                    que.push(P(nxt_v,start_v));
                }else if(dist[nxt_v][1].first == NIL && dist[nxt_v][0].second != start_v){
                    int now_id = dist[now_v][0].second == start_v ? 0 : 1;
                    dist[nxt_v][1] = P(dist[now_v][now_id].first + 1, start_v);
                    que.push(P(nxt_v,start_v));
                }
            }
        }
    };
    bfs();
    rep(i,n)if(s[i] == 'D')printf("%d\n",dist[i][0].first + dist[i][1].first);
    return 0;
}