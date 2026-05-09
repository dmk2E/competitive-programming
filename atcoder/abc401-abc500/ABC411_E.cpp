/*アルゴリズムと工夫点(E [max]/CPU: 184 ms Memory: 11708 KB  Length: 2898 B)
max の期待値は "X以下の期待値" と言い換えて解く．
(期待値)=Σ(確率変数の値)*(確率)
という形だけではなく，
(期待値)=Σ(確率変数がX以上のパターン数)/全パターン数=Σ(確率変数がX以上となる確率)
となることを利用する．
※公式解説を元にupsolve
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define DICE 6
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

    ll val()const{
        return this->val_;
    }
};

struct Data{
    int id,a;

    Data(int aa=0,int iid=0):a(aa),id(iid){}

    bool operator<(const Data& k)const{
        return a==k.a?id<k.id:a<k.a;
    }
};

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<Data> ipt;
    rep(i,n){
        rep(j,DICE){
            ll a;
            scanf("%lld",&a);
            ipt.push_back(Data(a,i));
        }
    }
    sort(ipt.begin(),ipt.end());
    int last=0,zero=n;
    vector<int> id_to_cnt(n,0);
    ModInt ans(0),prob(1),btm=ModInt(1)/ModInt(DICE)^(n);
    for(Data d:ipt){
        ModInt p=0;
        if(zero==0)p=prob*btm;
        ans=ans+(ModInt(1)-p)*(d.a-last);
        last=d.a;
        if(id_to_cnt[d.id]==0)zero--;else prob=prob/id_to_cnt[d.id];
        id_to_cnt[d.id]++;
        prob=prob*id_to_cnt[d.id];
    }
    printf("%lld\n",ans.val());
    return 0;
}