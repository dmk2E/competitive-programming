/*アルゴリズムと工夫点(A > B substring/CPU: 59 ms Memory: 14568 KB  Length: 4607 B)
座標圧縮 + BIT + 時系列処理 で解く．
sum_A, sum_B それぞれ，S[i, j) の'A'の数の累積和，S[i, j) の'B'の数の累積和とする．
部分文字列S[i, j) が条件を満たすには，
`（S[i, j) に含まれる'A'の数）= sum_A[j + 1] - sum_A[j] > sum_B[j + 1] - sum_B[j] = （S[i, j) に含まれる'B'の数）`
つまり，`sum_A[j + 1] - sum_B[j + 1] > sum_A[j] - sum_B[j]` である．
従ってjの値を固定した時，条件を満たすiの数は，`sum_A[i] - sum_B[i] > sum_A[j] - sum_B[j] (i > j)`を満たすiの数と同義である．
jの値を降順に時系列処理を行い，BIT を使用すれば，高速に値を計算できる．
sum_A[i] - sum_B[i] は負の数が含まれるため，座標圧縮も併用する．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class BinaryIndexedTree{
    int MOD = 998244353;
    vector<ll> bit;
public:
    /// @brief BITのコンストラクタ
    /// @param n 要素数
    BinaryIndexedTree(int n = 0){
        bit=vector<ll>(n + 1, 0);
    }

    /// @brief 初期化用
    /// @param n 要素数
    void init(int n){
        bit=vector<ll>(n + 1, 0);
    }

    /// @brief 一つの要素への加算処理
    /// @param k 1-indexed で添え字指定(0を指定してはダメ)
    /// @param dx 加算する値
    void add(int k,long long dx){//k=0を代入してはダメ
        assert(1 <= k && k < (int)bit.size());
        while(k<=bit.size()){
            bit[k] = (bit[k] + dx) % MOD;
            k += (k & (-k));
        }
    }

    /// @brief bit[1,k]の合計値を得る
    /// @param k 
    /// @return bit[1,k]の合計値
    ll sum(int k)const{
        ll s = 0;
        while(k > 0){
            s = (s + bit[k]) % MOD;
            k -= (k & (-k));
        }
        return s;
    }

    /// @brief bit[l,r]の合計値
    /// @param l 閉区間の左端
    /// @param r 閉区間の右端
    /// @return 閉区間の合計値
    ll ssum(int l,int r){
        assert(1 <=l && l < bit.size());
        assert(1 <= r &&r < bit.size());
        assert(l <= r);
        return (MOD + sum(r) - sum(l-1)) % MOD;
    }

    /// @brief BITのサイズ
    /// @return BITの要素数
    int size(){
        return (int)bit.size();
    }

    /// @brief 並列二分探索で，閾値以上となる添え字探索
    /// @param sum_val 閾値
    /// @return 添え字
    int lowerBound(ll sum_val){
        int left = 0, right = this->size(), mid;
        while(left < right){
            mid = (left + right) / 2;
            if(this -> sum(mid) < sum_val)left = mid + 1;
            else right = mid;
        }
        return left;
    }

    /// @brief 並列二分探索で，閾値より大きくなる添え字探索
    /// @param sum_val 閾値
    /// @return 添え字
    int upperBound(ll sum_val){
        int left = 0, right = this -> size(), mid;
        while(left < right){
            mid = (left + right) / 2;
            if(this->sum(mid) <= sum_val)left = mid + 1;
            else right = mid;
        }
        return left;
    }

    /// @brief BITの中身を表示する
    void show(){
        int i;
        rep(i, bit.size() - 2)
            printf("%lld ", sum(i + 1) - sum(i));
        printf("%lld\n", sum(i + 1) - sum(i));
    }
}BIT;

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

int n;
string s;

int main(){
    int i, j;
    ll ans = 0;
    scanf("%d", &n);
    cin >> s;
    vector<int> sum_a(n + 1, 0), sum_b(n + 1, 0);
    CC<int> ds;
    // BIT では座標0を扱えないため，その対策
    ds.add(-n - 1);
    rep(i, n){
        sum_a[i + 1] = sum_a[i] + (s[i] == 'A');
        sum_b[i + 1] = sum_b[i] + (s[i] == 'B');
        ds.add(sum_a[i + 1] - sum_b[i + 1]);
    }
    // sum_a[0] - sum_b[0] = 0 の分
    ds.add(0);
    BIT diff_tree(ds.size() + 1);
    for(i = n;i >= 0;i--){
        int tail_diff = ds(sum_a[i] - sum_b[i]);
        ans += diff_tree.ssum(tail_diff + 1, ds.size() + 1);
        diff_tree.add(tail_diff, 1);
    }
    printf("%lld\n", ans);
    return 0;
}