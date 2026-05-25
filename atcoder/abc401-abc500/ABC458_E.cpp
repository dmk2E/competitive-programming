/*アルゴリズムと工夫点(Count 123/CPU: 60 ms Memory: 50468 KB  Length: 3398 B)
グループ数を固定して数え上げる．
条件を満たす数列とは，「1」と「3」が隣り合わない事である．
そこで，「1」と「3」のグループ数を全探索し，その数が固定されている場合に，
1~3 の数の振り分け方を計算すればよい．
高速計算の為，逆元を利用する．
最悪計算量は，O(X1 + X2 + X3) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class Combination{
    int mod, max_num;
    vector<ll> fact, inv_fact;

    /// @brief 繰り返し自乗法で高速に累乗を計算する
    /// @param num 被累乗数
    /// @param pow 累乗数
    /// @return num ^ pow を mod で割った余り
    ll power(ll num, ll pow){
        ll val = 1, pow_num = num;
        while(pow > 0){
            if(pow & 1)val = (val * pow_num) % this -> mod;
            pow_num = (pow_num * pow_num) % this -> mod;
            pow >>= 1;
        }
        return val;
    }

public:
    /// @brief 組合せ nCr を計算するクラス
    /// @param max_num n の値としてとり得る最大値
    /// @param mod 計算にてとる余りの値
    Combination(int max_num, int mod = 998244353): max_num(max_num), mod(mod){
        int i;
        fact = vector<ll>(this -> max_num + 1);fact[0] = 1;
        rep(i, this -> max_num){
            fact[i + 1] = (fact[i] * (i + 1)) % this -> mod;
        }

        inv_fact = vector<ll>(this -> max_num + 1);
        inv_fact[this -> max_num] = this -> power(
            /* num = */ fact[this -> max_num], 
            /* pow = */ this -> mod - 2
        );
        for(i = this -> max_num - 1;i >= 0;i--)inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % this -> mod;
    }

    /// @brief n個の中からr個だけ選ぶ組合せの総数を求める
    /// @param n 選択肢の数
    /// @param r 選ぶ数
    /// @return nCr を mod で割った余り
    ll comb(int n, int r){
        assert(n >= r);
        return (((this -> fact[n] * this -> inv_fact[n - r]) % this -> mod) * this -> inv_fact[r]) % this -> mod;
    }

    /// @brief n個の箱に，r個のボールを振り分ける場合の数の総数を求める
    /// @param n 箱の数
    /// @param r ボールの数
    /// @return 総数を mod で割った余り
    ll countDistributions(int n, int r){
        // r個のボールを，n - 1 本の線で区切る方法の総数を求めると考えられるから，
        // 「n + r - 1 個の選択肢の内，r個だけボールとする場合の数」と言い換えられる
        return this -> comb(/* n = */ n + r - 1, r);
    }    
};

int x_1, x_2, x_3;

int main(){
    int i, j;
    scanf("%d%d%d", &x_1, &x_2, &x_3);

    Combination comb(/* max_num = */ x_1 + x_2 + x_3);
    ll ans = 0;
    rep(i, 2){
        for(int sum_group = 2;;sum_group++){
            int group_1 = sum_group / 2, group_3 = sum_group - group_1;
            if(group_1 > x_1 || group_3 > x_3)break;
            if(x_2 < sum_group - 1)break;

            int rest_1 = x_1 - group_1;
            ll now = comb.countDistributions(/* n = */ group_1, /* r = */ rest_1);
            
            int rest_3 = x_3 - group_3;
            now = (now * comb.countDistributions(/* n = */ group_3, /* r = */ rest_3)) % MOD;
            
            int rest_2 = x_2 - (sum_group - 1);
            now = (now * comb.countDistributions(/* n = */ x_1 + x_3 + 1, /* r = */ rest_2)) % MOD;

            ans = (ans + now) % MOD;
        }
        swap(x_1, x_3);
    }

    printf("%lld\n", ans);
    return 0;
}