/*アルゴリズムと工夫点(Divide Graph/CPU: 26 ms Memory: 9108 KB  Length: 3348 B)
Union-Find木を用いて解く．
今回の場合，辺1~(i - 1) のあらゆる組合せの重みの総和より，辺iの重みの方が大きくなる．
従って，重みが大きい辺はできるだけ削除しない方が良い．
ここで「辺の削除」は処理的に重いので，「辺を繋げる」処理に言い換えることを考える．
すると，辺が全くつながっていない状態からスタートし，重みの大きい順に辺を見ていき，
連結成分数が2個未満にならない限り辺をつなげる操作を繰り返せばよい．
繋がった辺の重みの総和を出力すればよい．
最悪計算量は，O(N + M) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
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

int n, m;

int main(){
    int i, connected;
    ll ans = 0;
    scanf("%d%d", &n, &m);
    connected = n;
    vector<ll> power_2(m + 1, 0);
    power_2[0] = 1;
    rep(i, m)power_2[i + 1] = (2 * power_2[i]) % MOD;
    vector<int> u(m), v(m);
    rep(i, m){
        scanf("%d%d", &u[i], &v[i]);
        u[i]--;v[i]--;
    }
    UF tree(n);
    for(i = m - 1;i >= 0;i--){
        if(!tree.isSame(/* node_a = */ u[i], /* node_b = */ v[i])){
            if(connected - 1 >= 2)tree.unite(/* node_a = */ u[i], /* node_b = */ v[i]), connected--;
            else ans = (ans + power_2[i + 1]) % MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}