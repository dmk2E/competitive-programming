/*アルゴリズムと工夫点(セグメント木/CPU: - ms Memory: - KB  Length: - B)
下記操作を O(log2(N)) （要素数:N）で行えるデータ構造．
 ・1要素の更新
 ・指定した区間の条件を満たす値
ここでいう「条件」とは"最大値"や"最小値"，"総和"などであり，関数の形で演算子 op の引数に渡す．
この時 op を用いて，対象となる要素の値 x との値を計算しても，x が必ず返されるような値を単位元 e とする．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

/// @brief セグ木を表すクラス
/// @tparam T セグ木に入れる要素の型
/// @tparam op 演算子
/// @tparam e 単位元（この値と演算しても結果が変わらない要素）
template<class T, auto op, auto e>
class SegTree{
    int count, size, offset;
    vector<T> tree;

    /// @brief 配列[begin, end) と 配列[now_begin, now_end) の共通範囲で，条件を満たす値を出力
    /// @param begin 半開区間の始端
    /// @param end 半開区間の終端
    /// @param node_id セグ木上の頂点番号
    /// @param now_begin セグ木上の頂点xが指している半開区間の始端
    /// @param now_end セグ木上の頂点xが指している半開区間の終端
    /// @return 区間 [begin, end) ∧ [now_begin, now_end) で，条件を満たす値
    T queryInternal(int begin, int end, int node_id, int now_begin, int now_end){
        if(now_end <= begin || end <= now_begin)return e;
        if(begin <= now_begin && now_end <= end)return this -> tree[node_id];

        return op(
            this -> queryInternal(
                /* begin = */ begin, 
                /* end = */ end, 
                /* node_id = */ 2 * node_id + 1, 
                /* now_begin = */ now_begin, 
                /* now_end = */ (now_begin + now_end) / 2
            ), this -> queryInternal(
                /* begin = */ begin, 
                /* end = */ end, 
                /* node_id = */ 2 * node_id + 2, 
                /* now_begin = */ (now_begin + now_end) / 2, 
                /* now_end = */ now_end
            )
        );
    }
public:
    /// @brief SegTreeのコンストラクタ
    /// @param count 要素数
    SegTree(int count){
        this -> count = count;

        this -> size = 1;
        while(this -> size < count)this -> size *= 2;
        tree = vector<T>(2 * (this -> size) - 1, e);
        offset = this -> size - 1;
    }

    /// @brief 配列上の指定した要素を取得する
    /// @param id 添え字を指定
    /// @return 指定されたセグ木上の葉の要素
    T operator[](int id) const{
        return this -> tree[offset + id];
    }

    /// @brief 現在の配列の要素を出力する（デバッグ用）
    void show() const{
        int i;
        for(i = 0; i < this -> size - 1 ; i++)cout << this -> tree[i + this -> offset] << ' ';
        cout << this -> tree[i + this -> offset] << '\n';
    }

    /// @brief 配列[begin, end)の範囲で，条件を満たす値を出力
    /// @param begin 半開区間の始端
    /// @param end 半開区間の終端
    /// @return 半開区間[begin, end)で，条件を満たす値
    T query(int begin, int end){
        return this -> queryInternal(
            /* begin = */ begin, 
            /* end = */ end, 
            /* node_id = */ 0, 
            /* now_begin = */ 0, 
            /* now_end */ this -> size
        );
    }

    /// @brief 配列上の特定の要素を始点とし，影響する全頂点を更新する
    /// @param id 添え字を指定
    /// @param x 更新のため与える値
    void operate(int id, T x){
        int node_id = id + this -> offset;
        this -> tree[node_id] = op(this -> tree[node_id], x);
        
        while(node_id > 0){
            node_id = (node_id - 1) / 2;
            this -> tree[node_id] = op(
                this -> tree[2 * node_id + 1], 
                this -> tree[2 * node_id + 2]
            );
        }
    }

    /// @brief 配列上の特定の要素を変更後，影響する全頂点を更新する
    /// @param id 添え字を指定
    /// @param x 変更する値
    void change(int id, T x){
        int node_id = id + this -> offset;
        this -> tree[node_id] = x;
        
        while(node_id > 0){
            node_id = (node_id - 1) / 2;
            this -> tree[node_id] = op(
                this -> tree[2 * node_id + 1], 
                this -> tree[2 * node_id + 2]
            );
        }
    }
};

int n, q, l, r;

ll op(ll a, ll b){
    return a + b;
}

int main(){
    int i;
    
    scanf("%d%d", &n, &q);
    SegTree<ll, op, 0> tree(n);
    
    while(q--){
        scanf("%d", &i);
        if(i == 1){
            scanf("%d%d", &l, &i);
            l--;
            tree.operate(/* id = */ l, /* x = */ i);
            tree.show();
        }else{
            scanf("%d%d", &l, &r);
            l--;
            printf("sum[%d, %d):%lld\n", l, 
                                         r, 
                                         tree.query(
                                            /* begin = */ l, 
                                            /* end = */ r
            ));
        }
    }
    return 0;
}