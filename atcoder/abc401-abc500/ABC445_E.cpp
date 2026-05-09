/*アルゴリズムと工夫点(Many LCMs/CPU: 493 ms Memory: 67236 KB  Length: 3691 B)
高速素因数分解 + 逆元 で解く．
配列の各要素を素因数分解し，素数ごとに，1, 2番目に大きい指数を保持しておく．
そうすることで，各要素が省かれた際のLCM を高速に求める．
この時，予め全要素のLCMを前計算しておくこと．
最悪計算量は，O(N * (log2(max(A)) + log2(MOD)) + max(A) * log2(max(A))) < 10 ^ 8 となり間に合う．
※ 素因数の個数は，実は大した数にはならない
※  2 * 3 * 5 * 7 * ...と昇順に素数をかけていくだけでもすぐに大きな数になる
*/
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A (int)(1e7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class PrimeMaster{
    const int NIL = -1;
    vector<int> min_fact;

public:
    const int MOD;
    vector<bool> is_prime;

    /// @brief 素数関係の処理をまとめたクラス
    /// @param max_val 扱う最大の正整数値（初期化処理：O(max_val * log2(max_val))）
    /// @param mod 割った余り
    PrimeMaster(int max_val, int mod = 998244353): MOD(mod){
        min_fact = vector<int>(max_val + 1, NIL);
        min_fact[0] = min_fact[1] = 1;

        // エラトステネスの篩で対象範囲内の整数について素数判定
        is_prime = vector<bool>(max_val + 1, true);
        is_prime[0] = is_prime[1] = false;
        for(int i = 2;i <= max_val;i++){
            if(is_prime[i]){
                min_fact[i] = i;
                int j = 2 * i;
                while(j <= max_val){
                    is_prime[j] = false;
                    min_fact[j] = i;
                    j += i;
                }
            }
        }
    }

    /// @brief 素朴な素数判定法（O(√N)）
    /// @param x 対象の正整数
    /// @return bool値: 素数か否か
    bool isPrime(int x){
        if(x == 2)return true;
        if(x <= 1 || x % 2 == 0)return false;
        for(int i = 3;i <= x / i;i += 2)if(x % i == 0)return false;
        return true;
    }

    /// @brief 高速な素因数分解を行う（O(log2(X))）
    /// @param x [0, max_val] 内の整数値
    /// @return vector<pair<int, int> >: 素因数分解の結果
    vector<pair<int, int> > convertToPFs(int x){
        vector<pair<int, int> > ans;
        while(x > 1){
            int divider = min_fact[x];
            ans.push_back(pair<int, int>(divider, 0));
            while(x % divider == 0){
                x /= divider;
                ans.back().second++;
            }
        }
        return ans;
    }
}PM;

typedef pair<int, int> P;

int t;
PM pm(MAX_A);

int power(int x, int a){
    long long ans = 1;
    while(a > 0){
        if(a & 1)ans = (ans * x) % pm.MOD;
        x = ((ll)x * x) % pm.MOD;
        a >>= 1;
    }
    return (int)ans;
}

void solve(){
    int i, j, n;
    ll all_lcm = 1;
    scanf("%d", &n);
    vector<int> a(n);
    map<int, vector<P> > pf_to_vec;
    rep(i, n)scanf("%d", &a[i]);
    // Aの各要素を高速素因数分解
    rep(i, n){
        for(auto [pf, cnt] : pm.convertToPFs(a[i])){
            if(pf_to_vec.find(pf) == pf_to_vec.end())pf_to_vec[pf].push_back(P(0, i));
            pf_to_vec[pf].push_back(P(cnt, i));
            sort(pf_to_vec[pf].rbegin(), pf_to_vec[pf].rend());
            if(pf_to_vec[pf].size() == 3)pf_to_vec[pf].pop_back();
        }
    }
    // Aの各要素を省いた時，全要素のLCMからどれだけ割るかを求める
    vector<int> id_to_divide(n, 1);
    for(auto [pf, vec] : pf_to_vec){
        auto [first_cnt, first_id] = vec[0];
        auto [second_cnt, second_id] = vec[1];
        int exp = power(pf, first_cnt);
        all_lcm = (all_lcm * exp) % pm.MOD;
        id_to_divide[first_id] = ((((ll)id_to_divide[first_id] * power(exp, pm.MOD - 2)) % pm.MOD) * power(pf, second_cnt)) % pm.MOD;
    }
    rep(i, n - 1)printf("%lld ", (all_lcm * id_to_divide[i]) % pm.MOD);
    printf("%lld\n", (all_lcm * id_to_divide[i]) % pm.MOD);
}

int main(){
    scanf("%d", &t);
    while(t--)solve();
    return 0;
}