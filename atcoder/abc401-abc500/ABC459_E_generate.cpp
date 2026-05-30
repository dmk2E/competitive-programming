/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#include<vector>
#include<random>
#include<time.h>
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

mt19937 mt_for_seed(time(NULL));

const int MAX_N = (int)(2e5);

int main(){
    int i, j;

    int n = (mt_for_seed() % MAX_N) + 1;
    printf("%d\n", n);
    
    UF tree(/* sum_nodes = */ n);
    vector<int> p;
    for(int i = 2;i <= n;i++){
        while(1){
            int par_node = (mt_for_seed() % n) + 1;
            if(tree.isSame(/* node_a = */ par_node - 1, /* node_b = */ i - 1))continue;
            p.push_back(par_node);
            break;
        }
    }
    rep(i, p.size() - 1)printf("%d ", p[i]);printf("%d\n", p[i]);

    vector<int> c;
    const int MAX_C = (int)(1e9);
    rep(i, n)c.push_back((mt_for_seed() % MAX_C) + 1);
    rep(i, c.size() - 1)printf("%d ", c[i]);printf("%d\n", c[i]);

    vector<int> d;
    const int MAX_D = 5;
    rep(i, n)d.push_back((mt_for_seed() % MAX_D) + 1);
    rep(i, d.size() - 1)printf("%d ", d[i]);printf("%d\n", d[i]);
    return 0;
}