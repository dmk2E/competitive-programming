/*アルゴリズムと工夫点(Count A%B=C/CPU: 19 ms Memory: 3928 KB  Length: 2339 B)
考察力+全探索 な問題．
考察により，A>B となる組の数から，A%B=0 となる数を引けばよいことが分かる．
つまり，Σ(1<=b<=N)floor(N/b) が求める解となる．
ここで，floor(N/b) のとり得る種類数が，2*√N となることを利用すると，一つの種類についてまとめて計算することで高速化が可能．
最悪計算量は，O(√N)<10^7 となり，高速．
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class ModInt{
    ll val_,MOD_;

    /// @brief 繰り返し二乗法でx^aを高速に求める
    /// @param x 被乗数
    /// @param a 乗数
    /// @return x^a
    ll power(ll x,ll a)const{
        ll ans=1;
        x%=MOD_;
        while(a>0){
            if(a&1)ans=(ans*x)%MOD_;
            x=(x*x)%MOD_;
            a>>=1;
        }
        return ans;
    }

public:

    ModInt(ll val=0,ll mod=998244353):val_(val%mod),MOD_(mod){}

    ModInt operator+(const ModInt& k)const{
        assert(MOD_==k.MOD_);
        return ModInt((val_+k.val_)%MOD_,MOD_);
    }

    ModInt operator+(const ll& k)const{
        return ModInt((val_+k%MOD_)%MOD_,MOD_);
    }

    ModInt operator-(const ModInt& k)const{
        assert(MOD_==k.MOD_);
        return ModInt((MOD_+val_-k.val_)%MOD_,MOD_);
    }

    ModInt operator-(const ll& k)const{
        return ModInt((MOD_+val_-k%MOD_)%MOD_,MOD_);
    }

    ModInt operator*(const ModInt& k)const{
        assert(MOD_==k.MOD_);
        return ModInt((val_*k.val_)%MOD_,MOD_); 
    }

    ModInt operator*(const ll& k)const{
        return ModInt((val_*(k%MOD_))%MOD_,MOD_);
    }

    ModInt operator^(const ModInt& k)const{
        assert(MOD_==k.MOD_);
        return ModInt(power(val_,k.val_),MOD_); 
    }

    ModInt operator^(const ll& k)const{
        return ModInt(power(val_,k),MOD_);
    }

    ModInt operator/(const ModInt& k)const{
        assert(MOD_==k.MOD_);
        return ModInt((val_*power(k.val_,MOD_-2))%MOD_,MOD_);
    }

    ModInt operator/(const ll& k)const{
        return ModInt((val_*power(k,MOD_-2))%MOD_,MOD_);
    }

    bool operator==(const ModInt& k)const{
        return val_==k.val_;
    }

    ModInt operator=(const ModInt& k){
        this->val_=k.val_;
        return *this;
    }

    ll val(){
        return val_;
    }
};

ll n;

int main(){
    int i,j;
    scanf("%lld",&n);
    ModInt ans(n+1);
    ans=ans*n/2;
    for(ll b=1;b<=n;){
        ll y=n/b;
        ll next_b=n/y+1;
        ans=ans-ModInt(next_b-b)*y;
        b=next_b;
    }
    printf("%lld\n",ans.val());
    return 0;
}