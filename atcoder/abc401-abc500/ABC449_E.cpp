/*アルゴリズムと工夫点(A += v/CPU: 107 ms Memory: 28892 KB  Length: 5815 B)
クエリ先読み + BIT で解く．
X の値の昇順にクエリを処理していくことを考える．
操作の単位を，最小の頻度が更新される前後に区切ると，この操作によって加えられる[1, M]の配列には法則性がある．
この配列を要素の昇順で保持し，任意番目の要素を高速に取り出せればよい．
これは BIT 上の高速探索で実現する．
最悪計算量は，O((N + Q) * (log2(Q) + log2(M))) < 10 ^ 7 となり高速．
※ クエリ先読みは、クエリの順番を都合の良いものにすることにも使用できる
*/
#include<iostream>
#include<vector>
#include<algorithm>
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

int n, m, q;

int main(){
    int i, j;
    scanf("%d%d", &n, &m);
    // 値毎の頻度を求める
    vector<int> a(n), num_to_freq(m + 1, 0);
    rep(i, n){
        scanf("%d", &a[i]);
        num_to_freq[a[i]]++;
    }
    
    // 頻度ごとに値を管理
    vector<vector<int> > freq_to_nums(n + 1);
    int max_freq = -1, now_freq = n + 1;
    for(i = 1;i <= m;i++){
        freq_to_nums[num_to_freq[i]].push_back(i);
        max_freq = max(max_freq, num_to_freq[i]);
        now_freq = min(now_freq, num_to_freq[i]);
    }

    // クエリ先読み
    scanf("%d", &q);
    vector<int> x_id(q);
    vector<ll> x(q);
    rep(i, q){
        scanf("%lld", &x[i]);
        x_id[i] = i;
    }
    //  クエリをxの昇順に管理
    sort(x_id.begin(), x_id.end(), [&](int a_id, int b_id) -> bool {
        return x[a_id] < x[b_id];
    });
    sort(x.begin(), x.end());

    // クエリ毎に解を求める
    ll arr_len = n, last_arr_len = n;
    BIT tree(/* len = */ m, /* mod = */ 1e18);
    vector<int> ans(q);
    rep(i, q){
        if(x[i] <= n)ans[x_id[i]] = a[x[i] - 1];
        else{
            while(now_freq <= max_freq && arr_len < x[i]){
                last_arr_len = arr_len;
                arr_len += freq_to_nums[now_freq].size() + tree.sum(/* right_id = */ m);
                for(int num : freq_to_nums[now_freq])tree.add(/* id = */ num, /* value = */ 1);
                now_freq++;
            }
            if(arr_len >= x[i])ans[x_id[i]] = tree.getMaxIdOfSum(/* sum = */ x[i] - 1 - last_arr_len) + 1;
            else ans[x_id[i]] = ((x[i] - arr_len - 1) % m) + 1;
        }
    }

    rep(i, q)printf("%d\n", ans[i]);
    return 0;
}