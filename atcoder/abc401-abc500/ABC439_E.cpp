/*アルゴリズムと工夫点(Kite/CPU: 104 ms Memory: 8272 KB  Length: 4890 B)
座標圧縮 + 平面走査 で解く．
凧のBiの値の最大値がY であった時の最大の凧の数をセグ木（Range Sum Query）で保持しておく．
すると，Aiの値の昇順に時系列処理をし，ある凧を選択した時，そのBiより小さい高さの範囲で，最大の凧の選択数をセグ木から高速で取得することを繰り返せばよい．
座標は非常に大きいので，座標圧縮を利用する．
最悪計算量は，O( N * log2(N) ) < 10^7 となり高速。
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
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
        xs=vector<T>(0);
        initiated = false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    int operator()(T k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    T operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(T x){
        initiated = false;
        xs.push_back(x);
    }

    /// @brief 特定の要素が存在するか判定する関数
    /// @param x 対象要素
    /// @return 判定結果
    bool exist(T x){
        int x_id = (*this)(x);
        return x_id < xs.size() && xs[x_id] == x;
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
};

/// @brief セグ木を表すクラス
/// @tparam T セグ木に入れる要素の型
/// @tparam op 演算子
/// @tparam e 単位元（この値と演算しても結果が変わらない要素）
template<class T, auto op, auto e>
class SegTree{
    int n, size, offset;
    vector<T> tree;

    /// @brief 配列[a, b)の範囲で，条件を満たす値を出力
    /// @param a 半開区間の始端
    /// @param b 半開区間の終端
    /// @param x セグ木上の頂点番号
    /// @param l セグ木上の頂点xが指している半開区間の始端
    /// @param r セグ木上の頂点xが指している半開区間の終端
    /// @return 半開区間[a, b)で，条件を満たす値
    T queryInternal(int a, int b, int node_id, int l, int r){
        if(r <= a || b <= l)return e;
        if(a <= l && r <= b)return this -> tree[node_id];
        return op(
            this -> queryInternal(a, b, 2 * node_id + 1, l, (l + r) / 2), 
            this -> queryInternal(a, b, 2 * node_id + 2, (l + r) / 2, r)
        );
    }
public:
    /// @brief SegTreeのコンストラクタ
    /// @param n 要素数
    SegTree(int n){
        this -> n = n;
        this -> size = 1;
        while(this -> size < n)this -> size *= 2;
        tree = vector<T>(2 * (this -> size) - 1, e);
        offset = this -> size - 1;
    }

    /// @brief 配列上の指定した要素を取得する
    /// @param id 添え字を指定
    /// @return 指定されたセグ木上の葉の要素
    T operator[](int id)const{
        return this -> tree[offset + id];
    }

    /// @brief 現在の配列の要素を出力する（デバッグ用）
    void show()const{
        int i;
        for(i = 0; i < this -> size - 1 ; i++)cout << this -> tree[i + this -> offset] << ' ';
        cout << this -> tree[i + this -> offset] << '\n';
    }

    /// @brief 配列[a, b)の範囲で，条件を満たす値を出力
    /// @param a 半開区間の始端
    /// @param b 半開区間の終端
    /// @return 半開区間[a, b)で，条件を満たす値
    T query(int a, int b){
        return this -> queryInternal(a, b, 0, 0, this -> size);
    }

    /// @brief 配列上の特定の要素を始点とし，影響する全頂点を更新する
    /// @param id 添え字を指定
    /// @param x 更新のため与える値
    void operate(int id, T x){
        int node_id = id + this -> offset;
        this -> tree[node_id] = op(this -> tree[node_id], x);
        while(node_id > 0){
            node_id = (node_id - 1) / 2;
            this -> tree[node_id] = op(this -> tree[node_id], x);
        }
    }
};

typedef pair<int,int> P;//(a,b)

int n;

int op(int a, int b){
    return max(a, b);
}

int main(){
    int i, ans = 0;
    CC<int> bs;
    bs.add(0);
    scanf("%d", &n);
    vector<P> ipt(n);
    rep(i, n){
        scanf("%d%d", &ipt[i].first, &ipt[i].second);
        bs.add(ipt[i].second);
    }
    SegTree<int, op, 0> tree(bs.size());
    sort(ipt.begin(), ipt.end(), [](P a, P b) -> bool{
        return a.first < b.first || 
              (a.first == b.first && a.second > b.second);
    });
    rep(i, n){
        ipt[i].second = bs(ipt[i].second);
        auto [a, b] = ipt[i];
        int val = tree.query(0, b) + 1;
        if(tree[b] < val)tree.operate(b, val);
        ans = max(ans, val);
    }
    printf("%d\n", ans);
    return 0;
}