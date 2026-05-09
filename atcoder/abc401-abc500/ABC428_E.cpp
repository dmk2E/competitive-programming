/*アルゴリズムと工夫点(Farthest Vertex/CPU: 412 ms Memory: 60012 KB  Length: 1000 B)
DFSを3回行って解く．
木の直径に端点となる点のペアかつ，頂点番号が大きいものが分かれば，解として出力されるのはその2つの番号のみとなる．
木の直径の端点を2回のDFSで求め，2回のDFSで解を求める．
この時2回目のDFSでは，片方の端点を解とする頂点群は求められるため，合計3回のDFSで済む．
最悪計算量は，O(N) < 10^7 となり高速．
※木に関して下記の性質が成立する．
・(木の直径)が偶数の場合：木の中心は1つの頂点となり，その頂点を中心にいくつかの部分木に分割して考察できる
・(木の直径)が奇数の場合：木の中心は辺となり，その辺を中心に2つの部分木に分けて考察できる
※ 木の直径はBFSを2回回して解くアルゴリズムは，"Double Sweep"という
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;

int main(){
    int i,j;
    scanf("%d", &n);
    vector<vector<int> > adj(n);
    vector<P> ans(n);
    while(--n){
        int a, b;
        scanf("%d%d",&a, &b);
        a--;b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // P(dist, vertex)
    auto dfs = [&](auto& func, int par, int now, P now_max)->P{
        ans[now] = max(ans[now], now_max);
        P ret(now_max.first, now);
        for(int nxt : adj[now])if(nxt != par){
            ret = max(ret, func(func, now, nxt, P(now_max.first + 1, now_max.second)));
        }
        return ret;
    };
    int a = dfs(dfs, 0, 0, P(0,0)).second, b = dfs(dfs, a, a, P(0, a)).second;
    dfs(dfs, b, b, P(0, b));
    for(P now : ans)printf("%d\n", now.second + 1);
    return 0;
}