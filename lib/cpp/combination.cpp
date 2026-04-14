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

    /// @brief N個の中からr個だけ選ぶ組合せの総数を求める
    /// @param n 選択肢の数
    /// @param r 選ぶ数
    /// @return nCr を mod で割った余り
    ll comb(int n, int r){
        assert(n >= r);
        return (((this -> fact[n] * this -> inv_fact[n - r]) % this -> mod) * this -> inv_fact[r]) % this -> mod;
    }
};

int main(){
    // お試し
    Combination comb(/* max_num = */ 1000000);
    while(1){
        int n, r;
        scanf("%d%d", &n, &r);
        printf("%lld\n", comb.comb(/* n = */ n, /* r = */ r));
    }
    return 0;
}