/*アルゴリズムと工夫点(Simple Division/CPU: 335 ms Memory: 4364 KB  Length: 3411 B)
逆元と再帰を利用して解く．
今回の問題はレピュニット数の逆元を高速に求める部分が課題で，逆元が取れない可能性があることである．
そこで繰り返し自乗法と似た手法で，商を用いない手法で解を計算する．
最悪計算量は，O(K * (log2(max(l) + log2(MOD)))) < 10 ^ 7 となり高速．
※ floor(y / x) = (y - y % x) / x という式変形を用いていることに注意
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 10007
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
        this->val_ = k.val_;
        return *this;
    }

    ll val(){
        return val_;
    }
};

int k, m;

int power(int x, ll a){
    ll ans = 1;
    x %= m;
    while(a > 0){
        if(a & 1)ans = (ans * x) % m;
        x = (x * x) % m;
        a >>= 1;
    }
    return ans;
}

int calcRep(int num, int len){
    if(len == 0)return 0;
    if(len % 2 == 0){
        int tmp = calcRep(/* num */num, /* len = */ len / 2);
        return ((tmp * power(10, len / 2)) % m + tmp) % m;
    }
    return ((calcRep(/* num = */ num, /* len = */ len - 1) * 10) % m + num) % m;
}

int main(){
    int i, j;
    ll min_l = 0;
    scanf("%d%d", &k, &m);
    vector<int> c(k), l(k);
    ModInt n(/* val = */ 0, /* mod = */ MOD);
    ll sum_mod_m = 0;
    rep(i, k)scanf("%d%d", &c[i], &l[i]);
    rep(i, k){
        if(c[k - 1 - i] == 0){
            min_l += l[k - 1 - i];
            continue;
        }
        sum_mod_m = (sum_mod_m + (calcRep(/* num = */ c[k - 1 - i], /* len = */ l[k - 1 - i]) * power(10, min_l)) % m) % m;
        n = n + ModInt(c[k - 1 - i], MOD) * (((ModInt(10, MOD) ^ (min_l + l[k - 1 - i])) - (ModInt(10, MOD) ^ min_l)) / ModInt(9, MOD));
        min_l += l[k - 1 - i];
    }
    printf("%lld\n", ((n - sum_mod_m) / m).val());
    return 0;
}