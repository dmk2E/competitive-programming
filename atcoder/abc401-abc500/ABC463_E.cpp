/*アルゴリズムと工夫点(Roads and Gates/CPU: 196 ms Memory: 29572 KB  Length: 1830 B)
超頂点 + ダイクストラ法で解く．
都市を頂点，道路を辺とする有向グラフを考える．
このグラフに加え，ワープゲート自体を表す頂点を用意し，N個の頂点と下記のような重みを付けた辺を張る．
 ・各頂点 i (∈ [1, N]) -> 頂点0 : Xi + Y の重み
 ・頂点0 -> 各頂点 i (∈ [1, N]) : Xi の重み
このグラフ上で最短経路問題を解けばよく，これはダイクストラ法で解ける．
最悪計算量は，O((N + M) * log2(N + M)) < 10 ^ 7 となり，高速．
※ もしワープゲートを通る経路の方が，そうでない経路よりかかる時間が短くなるならば，
   他の頂点と同様にワープゲートへの到達時間が最短のものだけを考慮すればよいため．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> P; //(to, cost)

struct Info{
    int to;
    ll cost;

    Info(int to = 0, ll cost = 0):to(to), cost(cost){}

    bool operator<(const Info& k)const{
        return cost > k.cost || (cost == k.cost && to < k.to);
    }
};

int n, m, y;

int main(){
    int i, j;

    scanf("%d%d%d", &n, &m, &y);
    vector<vector<P> > adj(n + 1);
    while(m--){
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        adj[u].push_back(P(v, t));
        adj[v].push_back(P(u, t));
    }
    rep(i, n){
        int x;
        scanf("%d", &x);
        adj[0].push_back(P(i + 1, x));
    }
    rep(i, n)adj[i + 1].push_back(P(0, adj[0][i].second + y));

    const int NIL = -1;
    vector<ll> min_time(n + 1, NIL);
    auto dijk = [&]() -> void{
        priority_queue<Info> PQ;
        PQ.push(Info(
            /* to = */ 1, 
            /* cost = */ 0
        ));

        while(PQ.size()){
            Info now;
            do{
                now = PQ.top();PQ.pop();
            }while(PQ.size() && min_time[now.to] != NIL);

            if(min_time[now.to] != NIL)break;
            min_time[now.to] = now.cost;

            for(auto [nxt_to, nxt_cost] : adj[now.to]){
                if(min_time[nxt_to] == NIL){
                    PQ.push(Info(
                        /* to = */ nxt_to, 
                        /* cost = */ now.cost + nxt_cost
                    ));
                }
            }
        }
    };
    dijk();

    for(i = 2;i < n;i++)printf("%lld ", min_time[i]);
    printf("%lld\n", min_time[i]);
    return 0;
}