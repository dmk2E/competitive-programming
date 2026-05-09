/*アルゴリズムと工夫点(Relative Position/CPU: 126 ms Memory: 21272 KB  Length: 1332 B)
BFSで解く．
人毎に頂点を用意し，座標を保持させ，相対関係を重みとしてもつ辺を張ったグラフを考える．
このグラフ上で原点を始点とする探索を行い，順次座標を求めればよい．
最悪計算量は，O(N + M) < 10^6 となり，高速．
※ 与えられる情報に矛盾がないため，一つの頂点としてあり得る座標のパターンが複数あることはない
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int id, x, y;

    Data(int id = 0, int x = 0, int y = 0):id(id), x(x), y(y){}
};

typedef pair<ll,ll> P;

int n,m;

int main(){
    int i,j;
    const ll INF = (1e15);
    const P NIL = P(INF, INF);
    scanf("%d%d", &n, &m);
    vector<vector<Data> > adj(n);
    while(m--){
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);a--;b--;
        adj[a].push_back(Data(b, x, y));
        adj[b].push_back(Data(a, -x, -y));
    }
    vector<P> vis(n, NIL);
    auto bfs = [&]() -> void{
        queue<int> que;
        vis[0] = P(0, 0);
        que.push(0);
        while(que.size()){
            int now = que.front();que.pop();
            for(auto [nxt, x, y] : adj[now]){
                P nxt_p = P(vis[now].first + x, vis[now].second + y);
                if(vis[nxt] == NIL){
                    vis[nxt] = nxt_p;
                    que.push(nxt);
                }
            }
        }
    };
    bfs();
    rep(i, n){
        if(vis[i] == NIL)puts("undecidable");
        else printf("%lld %lld\n", vis[i].first, vis[i].second);
    }
    return 0;
}