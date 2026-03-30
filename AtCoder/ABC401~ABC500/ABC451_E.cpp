/*アルゴリズムと工夫点(Tree Distance/CPU: 541 ms Memory: 137240 KB  Length: 4544 B)
クラスカル法 + DFS で解く．
渡される辺の重みの総和が最小のものについては，必ずその頂点間を直接つなぐ辺が存在する．
そうでない2頂点間について，既に張った辺によって連結していない場合のみ，その2頂点間を直接繋ぐ辺を追加していけば良い．
連結である場合は，もしAが存在するのであれば，追加する必要性がない．
その後，構築したMST木について，A の条件を満たすか，DFSで判定すればよい．
最悪計算量は，O(N ^ 2) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> par, rank, cnt;
    const int NIL = -1;
public:
    /// @brief Union-Find木を扱うクラス
    /// @param sum_nodes 管理する頂点数
    UnionFindTree(int sum_nodes = 0){
        int i;
        rep(i, sum_nodes)par.push_back(i);
        rank = vector<int>(sum_nodes, 0);
        cnt = vector<int>(sum_nodes, 1);
    }

    /// @brief 指定した頂点が属する集合の代表頂点の番号を返す
    /// @param node_id 頂点番号
    /// @return int型
    int root(int node_id){
        return this -> par[node_id] == node_id ? node_id : this -> par[node_id] = this -> root(this -> par[node_id]);
    }

    /// @brief 2つの頂点が同じ集合に属しているか判定する
    /// @param node_a 1つ目の頂点番号
    /// @param node_b 2つ目の頂点番号
    /// @return bool型
    bool isSame(int node_a, int node_b){
        return this -> root(node_a) == this -> root(node_b);
    }

    /// @brief 2つの頂点が属する集合を併合し，新たな代表頂点の番号を返す
    /// @param node_a 1つ目の頂点番号
    /// @param node_b 2つ目の頂点番号
    /// @return int型
    int unite(int node_a, int node_b){
        node_a = this -> root(node_a);
        node_b = this -> root(node_b);
        if(node_a == node_b)return NIL;
        if(this -> rank[node_a] < this -> rank[node_b]){
            this -> par[node_a] = node_b;
            this -> cnt[node_b] += cnt[node_a];
            return node_b;
        }else{
            this -> par[node_b] = node_a;
            this -> cnt[node_a] += cnt[node_b];
            if(this -> rank[node_a] == this -> rank[node_b])this -> rank[node_a]++;
            return node_a;
        }
    }

    /// @brief 指定された頂点が属する集合に含まれる頂点数を返す
    /// @param node_id 頂点番号
    /// @return int型
    int count(int node_id){
        return this -> cnt[this -> root(node_id)];
    }

    /// @brief 木の現在の情報出力
    void show(){
        int i;
        printf("par:");rep(i, this -> rank.size())printf("%d ", this -> par[i]);puts("");
        printf("cnt:");rep(i, this -> rank.size())printf("%d ", this -> cnt[root(i)]);puts("");
    }

    /// @brief Union-Find木が管理している頂点数を返す
    /// @return int型
    int size(){
        return this -> par.size();
    }
}UF;

struct Edge{
    int u, v, cost;

    Edge(int u = 0, int v = 0, int cost = 0):v(v), u(u), cost(cost){}

    bool operator<(const Edge& k)const{
        return cost < k.cost;
    }
};

struct ToEdge{
    int to, cost;

    ToEdge(int to = 0, int cost = 0):to(to), cost(cost){}
};

int n;

int main(){
    int i, j;
    scanf("%d", &n);
    vector<Edge> edges;
    const int NIL = -1;
    vector<vector<int> > a(n, vector<int>(n, NIL));
    rep(i, n)for(j = i + 1;j < n;j++){
        scanf("%d", &a[i][j]);
        a[j][i] = a[i][j];
        edges.push_back(Edge(i, j, a[i][j]));
    }
    sort(edges.begin(), edges.end());
    
    // MST を構築
    UF tree(n);
    vector<vector<ToEdge> > adj(n);
    for(auto [u, v, cost] : edges){
        if(!tree.isSame(u, v)){
            adj[u].push_back(ToEdge(v, cost));
            adj[v].push_back(ToEdge(u, cost));
            tree.unite(u, v);
        }
    }

    // 条件を満たすか判定
    auto dfs = [&](auto& func, int par, int root, int now, int sum) -> bool{
        if(root != now && a[root][now] != sum)return false;
        for(auto [to, cost] : adj[now]){
            if(
                to != par && 
                !func(
                    /* func = */ func, 
                    /* par = */ now, 
                    /* root = */ root, 
                    /* now = */ to, 
                    /* sum = */ sum + cost
                )
            )return false;
        }
        return true;
    };
    rep(i, n)
        if(
            !dfs(
                /* func = */ dfs, 
                /* par = */ NIL, 
                /* root = */ i, 
                /* now = */ i, 
                /* sum = */ 0
            )
        ){
            puts("No");
            return 0;
        }
    puts("Yes");
    return 0;
}