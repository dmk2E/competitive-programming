/*アルゴリズムと工夫点(Integer-duplicated Path/CPU: 126 ms Memory: 33356 KB  Length: 2732 B)
連想配列 + DFS で解く．
頂点1から深さ優先探索を行うが，各頂点iに到達時，
それまでに訪れた頂点に書かれた整数それぞれの個数を記録しておく．
そうすると，頂点1から頂点iまでの単純パス内に同じ整数が書かれた整数が存在するか否かが判定できる．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
※ 連想配列mapは処理が重いので，代わりに座標圧縮を用いた
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class CC{
    bool initiated;
    vector<T> xs;
public:
    /// @brief 座標圧縮（CoordinatedCompression）のクラス
    CC(){
        xs = vector<T>(0);
        initiated = false;
    }
private:
    void init(){
        initiated = true;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
public:
    int operator()(T value){
        if(!initiated)init();
        return lower_bound(xs.begin(), xs.end(), value) - xs.begin();
    }

    T operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 要素を追加する関数
    /// @param value 追加する座標
    void add(T value){
        initiated = false;
        xs.push_back(value);
    }

    /// @brief 特定の要素が存在するか判定する関数
    /// @param value 対象要素
    /// @return 判定結果
    bool exist(T value){
        int value_id = (*this)(value);
        return value_id < xs.size() && xs[value_id] == value;
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
};

int n;

int main(){
    int i, j;
    scanf("%d", &n);
    vector<int> a(n), cc_a(n);
    vector<vector<int> > adj(n);
    CC<int> as;
    rep(i, n){
        scanf("%d", &a[i]);
        as.add(a[i]);
    }
    rep(i, n)cc_a[i] = as(/* value = */ a[i]);
    rep(i, n - 1){
        int u, v;
        scanf("%d%d", &u, &v);
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int valid_nums = 0;
    vector<bool> is_valid(n, false);
    vector<int> a_to_cnt(as.size(), 0);
    auto dfs = [&](auto& func, int prev_node, int now_node) -> void{
        if(a_to_cnt[cc_a[now_node]] == 1)valid_nums++;
        a_to_cnt[cc_a[now_node]]++;
        is_valid[now_node] = valid_nums > 0;
        for(int nxt_node : adj[now_node]){
            if(nxt_node == prev_node)continue;
            func(
                /* func = */ func, 
                /* prev_node = */ now_node, 
                /* now_node = */ nxt_node
            );
        }
        if(a_to_cnt[cc_a[now_node]] == 2)valid_nums--;
        a_to_cnt[cc_a[now_node]]--;
    };
    const int NIL = -1;
    dfs(/* func = */ dfs, /* prev_node = */ NIL, /* now_node = */ 0);
    rep(i, n)printf("%s\n", is_valid[i] ? "Yes" : "No");
    return 0;
}