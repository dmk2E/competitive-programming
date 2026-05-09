/*アルゴリズムと工夫点(Playlist/CPU: 33 ms Memory: 3856 KB  Length: 2664 B)
動的計画法 + 逆元 で解く．
下記のDPテーブルを前計算で求めておく．
dp[i] := i秒目でちょうど曲が終了する確率
このテーブルの値が分かれば，求める確率は
Σ(i ∈ [max(0, X + 1 - T_{1}), X]) dp[i] となる．
最悪計算量は，O(N * X) < 10 ^ 8 となり間に合う．
※ 本コードでは，1 / N の逆元を前計算で求めておくことで高速化している
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class ModInt{
    ll val_, MOD_;

    /// @brief 繰り返し二乗法でx^aを高速に求める
    /// @param x 被乗数
    /// @param a 乗数
    /// @return x^a
    ll power(ll x, ll a)const{
        ll ans = 1;
        x %= MOD_;
        while(a > 0){
            if(a & 1)ans = (ans * x) % MOD_;
            x = (x * x) % MOD_;
            a >>= 1;
        }
        return ans;
    }

public:

    ModInt(ll val = 0,ll mod = 998244353):val_(val % mod), MOD_(mod){}

    ModInt operator+(const ModInt& k)const{
        assert(MOD_ == k.MOD_);
        return ModInt((val_ + k.val_) % MOD_, MOD_);
    }

    ModInt operator+(const ll& k)const{
        return ModInt((val_ + k % MOD_) % MOD_, MOD_);
    }

    ModInt operator-(const ModInt& k)const{
        assert(MOD_ == k.MOD_);
        return ModInt((MOD_ + val_ - k.val_) % MOD_, MOD_);
    }

    ModInt operator-(const ll& k)const{
        return ModInt((MOD_ + val_ - k % MOD_) % MOD_, MOD_);
    }

    ModInt operator*(const ModInt& k)const{
        assert(MOD_ == k.MOD_);
        return ModInt((val_ * k.val_) % MOD_, MOD_); 
    }

    ModInt operator*(const ll& k)const{
        return ModInt((val_ * (k % MOD_)) % MOD_, MOD_);
    }

    ModInt operator^(const ModInt& k)const{
        assert(MOD_ == k.MOD_);
        return ModInt(power(val_, k.val_), MOD_); 
    }

    ModInt operator^(const ll& k)const{
        return ModInt(power(val_, k), MOD_);
    }

    ModInt operator/(const ModInt& k)const{
        assert(MOD_ == k.MOD_);
        return ModInt((val_ * power(k.val_, MOD_ - 2)) % MOD_, MOD_);
    }

    ModInt operator/(const ll& k)const{
        return ModInt((val_ * power(k, MOD_ - 2)) % MOD_, MOD_);
    }

    bool operator==(const ModInt& k)const{
        return val_ == k.val_;
    }

    ModInt operator = (const ModInt& k){
        this -> val_ = k.val_;
        return *this;
    }

    ll val(){
        return val_;
    }
};

int n, x;

int main(){
    int i, j;
    scanf("%d%d", &n, &x);
    vector<int> t(n);
    rep(i, n)scanf("%d", &t[i]);

    ModInt inv_n = ModInt(1) / n;
    vector<ModInt> dp(x + 1);
    dp[0] = 1;
    rep(i, x + 1)rep(j, n)
        if(i + t[j] <= x)dp[i + t[j]] = dp[i + t[j]] + dp[i] * inv_n;

    ModInt ans;
    for(i = max(0, x + 1 - t[0]);i <= x;i++)ans = ans + dp[i] * inv_n;
    printf("%lld\n", ans.val());
    return 0;
}