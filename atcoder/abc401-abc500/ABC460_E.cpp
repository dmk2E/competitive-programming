/*アルゴリズムと工夫点(x + y ≡ x + y/CPU: 19 ms Memory: 3756 KB  Length: 3262 B)
concat(x, y) の内，y の桁数を固定して，数え上げる．

concat(a, b) = a * 10 ^ (log10(b)) + b より，
concat(a, b) ≡ a + b -> a * 10 ^ (log10(b)) ≡ a -> a * (10 ^ (log10(b)) - 1) ≡ 0
よって，下記の方針が成り立つ．
 ・b の桁数 を固定すると，20通り
 ・(10 ^ digit - 1) % m = b_mod とする
   a * b_mod = 0 となるためには，a が m の約数を持てばよいから，
   m / gcd(m, b_mod) の倍数の数を求めればよい

したがって，最悪計算量は，O(T * log10(N) * log(M)) < 10 ^ 7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class ModInt{
    ull val_, mod_;

    /// @brief 繰り返し二乗法でx^aを高速に求める
    /// @param x 被乗数
    /// @param a 乗数
    /// @return x^a
    ull power(ull x, ull a)const{
        ull ans = 1;
        x %= this -> mod_;
        while(a > 0){
            if(a & 1)ans = (ans * x) % this -> mod_;
            x = (x * x) % this -> mod_;
            a >>= 1;
        }
        return ans;
    }

public:

    ModInt(ull val = 0, ll mod = 998244353):val_(val % mod), mod_(mod){}

    ModInt operator+(const ModInt& k)const{
        assert(this -> mod_ == k.mod_);
        return ModInt((this -> val_ + k.val_) % this -> mod_, this -> mod_);
    }

    ModInt operator+(const ull& k)const{
        return ModInt((this -> val_ + k % this -> mod_) % this -> mod_, this -> mod_);
    }

    ModInt operator-(const ModInt& k)const{
        assert(this -> mod_ == k.mod_);
        return ModInt((this -> mod_ - k.val_ + val_) % this -> mod_, this -> mod_);
    }

    ModInt operator-(const ull& k)const{
        return ModInt((this -> mod_ + val_ - k % this -> mod_) % this -> mod_, this -> mod_);
    }

    ModInt operator*(const ModInt& k)const{
        assert(this -> mod_ == k.mod_);
        return ModInt((this -> val_ * k.val_) % this -> mod_, this -> mod_); 
    }

    ModInt operator*(const ll& k)const{
        return ModInt((val_ * (k % this -> mod_)) % this -> mod_, this -> mod_);
    }

    ModInt operator^(const ModInt& k)const{
        assert(this -> mod_ == k.mod_);
        return ModInt(power(this -> val_, k.val_), this -> mod_); 
    }

    ModInt operator^(const ll& k)const{
        return ModInt(power(this -> val_, k), this -> mod_);
    }

    ModInt operator/(const ModInt& k)const{
        assert(this -> mod_ == k.mod_);
        return ModInt((val_ * power(k.val_, this -> mod_ - 2)) % this -> mod_, this -> mod_);
    }

    ModInt operator/(const ll& k)const{
        return ModInt((val_ * power(k, this -> mod_ - 2)) % this -> mod_, this -> mod_);
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

int t;

ll gcd(ll num_1, ll num_2){return num_2 == 0 ? num_1 : gcd(num_2, num_1 % num_2);}

int solve(){
    ll n, m;
    scanf("%lld%lld", &n, &m);

    ModInt ans(/* val = */ 0);
    ull ten_power = 10, range_begin = 1, range_end = 10;
    while(range_begin <= n){
        ll b = (m - 1 + (ten_power % m)) % m;
        ll a_rest = m / gcd(/* num_1 = */ m, /* num_2 = */ b);

        ans = ans + 
              ModInt(/* val = */ n / a_rest) * 
              ModInt(/* val = */ min(range_end, (ull)n + 1) - range_begin);

        range_begin = range_end;
        range_end *= 10;
        ten_power *= 10;
    }
    return (int)ans.val();
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%d\n", solve());
    return 0;
}