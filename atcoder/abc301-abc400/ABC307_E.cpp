/*アルゴリズムと工夫点(Distinct Adjacent/CPU: 17 ms Memory: 3868 KB  Length: 2392 B)
対称性を利用したDPで解く．
つまり先頭の値が0である時の場合の数を求め，それをM倍すれば解となる．
またこの時，最後に割り当てた値が0であるか否か，の2通りのみ考慮すれば問題ない．
従って，以下のDPを解く．
dp[i][j]:i番目の人に割り当てる整数を決めた時，その値が j=0:0である j=1:0でない 時の場合の数
最悪計算量は，O(N) < 10^7 となり高速．
※場合の数の数え上げにも，DPが適用できることを覚えておこう．
*/
#include<iostream>
#include<vector>
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

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<ModInt> dp(2,0);
    dp[0]=1;
    rep(i,n-1){
        vector<ModInt> now(2,0);
        now[0]=now[0]+dp[1];
        now[1]=dp[0]*(m-1)+dp[1]*(m-2);
        swap(dp,now);
    }
    printf("%lld\n",(dp[1]*m).val());
    return 0;
}