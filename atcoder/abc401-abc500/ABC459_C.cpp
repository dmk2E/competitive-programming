/*アルゴリズムと工夫点(Drop Blocks/CPU: 50 ms Memory: 7192 KB  Length: 4915 B)
BIT で解く．
マス毎に積まれたブロック数を一次元配列で保持しつつ，ブロック数毎のマスの数をBITで保持してシミュレーションを行う．
最悪計算量は，O(N + Q * log2(N)) < 10 ^ 7 となり高速．
※ ある値X以上の要素数の管理は，一次元配列で実現できる
※  cnt_over[x] := x以上の値をもつ要素数
※  1. 初期状態は愚直に更新
※  2. Xである要素の値を +1 する場合，cnt_over[X + 1] += 1 のように更新する
※ 今回BITで実装してしまったが，公式解説のこちらの方が計算量も実装も軽くなる
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class BinaryIndexedTree{
    ll mod = 998244353;
    vector<ll> bit;
public:
    /// @brief BITのコンストラクタ
    /// @param len 要素数
    /// @param mod 除数
    BinaryIndexedTree(int len = 0, ll mod = -1){
        this -> bit = vector<ll>(len + 1, 0);
        this -> mod = max(this -> mod, mod);
    }

    /// @brief 初期化用
    /// @param len 要素数
    void init(int len){
        this -> bit = vector<ll>(len + 1, 0);
    }

    /// @brief 一つの要素への加算処理
    /// @param id 1-indexed で添え字指定(0を指定してはダメ)
    /// @param value 加算する値
    void add(int id, long long value){//id = 0を代入してはダメ
        assert(1 <= id && id < (int)bit.size());
        while(id <= bit.size()){
            bit[id] = (bit[id] + value) % this -> mod;
            id += (id & (-id));
        }
    }

    /// @brief bit[1,k]の合計値を得る
    /// @param right_id 
    /// @return bit[1,k]の合計値
    ll sum(int right_id)const{
        ll ans = 0;
        while(right_id > 0){
            ans = (ans + this -> bit[right_id]) % this -> mod;
            right_id -= (right_id & (-right_id));
        }
        return ans;
    }

    /// @brief bit[l,r]の合計値
    /// @param l 閉区間の左端
    /// @param r 閉区間の右端
    /// @return 閉区間の合計値
    ll ssum(int l,int r)const{
        assert(1 <= l && l < bit.size());
        assert(1 <= r && r < bit.size());
        assert(l <= r);
        return (this -> mod + sum(r) - sum(l - 1)) % this -> mod;
    }

    /// @brief BITのサイズ
    /// @return BITの要素数
    int size(){
        return (int)bit.size();
    }

    /// @brief 配列の一要素へのアクセス
    /// @param id 添え字
    /// @return 指定した添え字に位置する値
    ll operator[](const int id)const{
        return this -> ssum(id, id);
    }

    /// @brief その合計値をとる区間 [1, k] において，最大のkを返す（最悪計算量 log2(配列のサイズ)）
    /// @param sum 合計値
    /// @return int型（1-indexed の値）
    int getMaxIdOfSum(ll sum)const{
        int id = 0, power_of_two = 1;
        while((power_of_two << 1) < bit.size())power_of_two <<= 1;
        for(;power_of_two > 0;power_of_two >>= 1){
            if(id + power_of_two >= bit.size())continue;
            if(bit[id + power_of_two] <= sum){
                sum -= bit[id + power_of_two];
                id += power_of_two;
            }
        }
        return id;
    }

    /// @brief 並列二分探索で，閾値以上となる添え字探索
    /// @param sum_val 閾値
    /// @return 添え字
    int lowerBound(ll sum_val){
        int left = 0, right = this -> size(), mid;
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
            if(this -> sum(mid) <= sum_val)left = mid + 1;
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

    /// @brief BITで保持している配列を表示する
    void showBITArr(){
        int i;
        rep(i, bit.size())printf("id = %d: %lld\n", i, bit[i]);
    }
}BIT;

int n, q;

int main(){
    int i, j;
    scanf("%d%d", &n, &q);
    vector<int> id_to_blocks(n, 0);
    const int MAX_LEN = q + 2;
    BIT tree(/* len = */ MAX_LEN);
    tree.add(/* id = */ 1, /* value = */ n);

    int all_minus_cnt = 0;
    while(q--){
        int k;
        scanf("%d", &k);
        if(k == 1){
            scanf("%d", &k);k--;
            tree.add(/* id = */ id_to_blocks[k] + 1, /* value = */ -1);
            id_to_blocks[k]++;
            tree.add(/* id = */ id_to_blocks[k] + 1, /* value = */ 1);

            if(tree.ssum(/* l = */ all_minus_cnt + 2, /* r = */ MAX_LEN) >= n)all_minus_cnt++;
        }else{
            scanf("%d", &k);
            printf("%lld\n", k + all_minus_cnt + 1 < MAX_LEN ? tree.ssum(/* l = */ k + all_minus_cnt + 1, /* r = */ MAX_LEN) : 0);
        }
    }
    return 0;
}