/*アルゴリズムと工夫点(Distribute Bunnies/CPU: 146 ms Memory: 28492 KB  Length: 2389 B)
（座圧 + ）グラフ問題に落とし込む．
ウサギの移動先候補の2つの場所を2頂点とし，辺で結んだグラフを考える．
その辺において向きをどちらかにするか決め，向きを指された頂点の個数を数え上げればよい．
その時，連結成分ごとに解を出すことができ，頂点の個数と辺の個数によって値は2通り存在する．
最悪計算量は，O( N * log2(N) )
※ (辺の個数) = (頂点の次数の合計数) / 2 となることを覚えておこう
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class CoordinatedCompression{
    bool initiated;
    vector<int> xs;
public:
    CoordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(int x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(int k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    int operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
}CC;

typedef pair<int,int> P;

int n;

int main(){
    int i,j,ans = 0;
    scanf("%d",&n);
    CC xs;
    vector<int> x(n),r(n);
    rep(i,n){
        scanf("%d%d",&x[i], &r[i]);
        xs.add(x[i] - r[i]);xs.add(x[i] + r[i]);
    }
    vector<vector<int> > adj(xs.size());
    rep(i,n){
        int left = xs(x[i] - r[i]), right = xs(x[i] + r[i]);
        adj[left].push_back(right);
        adj[right].push_back(left);
    }
    vector<bool> is_visited(xs.size(), false);
    auto bfs = [&](int s) -> int {
        int i, vertex_count = 1, edge_count = 0;
        queue<int> que;
        is_visited[s] = true;
        que.push(s);
        edge_count += adj[s].size();
        while(que.size()){
            int now = que.front();que.pop();
            for(int nxt : adj[now]){
                if(is_visited[nxt] == false){
                    is_visited[nxt] = true;
                    que.push(nxt);
                    vertex_count++;
                    edge_count += adj[nxt].size();
                }
            }
        }
        edge_count /= 2;
        return min(vertex_count, edge_count);
    };
    rep(i,xs.size())if(is_visited[i] == false)ans += bfs(i);
    printf("%d\n", ans);
    return 0;
}