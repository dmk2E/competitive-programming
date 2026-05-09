/*アルゴリズムと工夫点(Fruit Lineup/CPU: 69 ms Memory: 65824 KB  Length: 1121 B)
関係性をグラフで表し，リンゴの最後の位置を固定して全探索する．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,d;
vector<ll> fac,inv_fac;

ll power(ll x,int a){
    ll ans=1;
    while(a>0){
        if(a&1)ans=((ans%MOD)*x)%MOD;
        x=((x%MOD)*(x%MOD))%MOD;
        a>>=1;
    }
    return ans;
}

ll comb(int n,int c){
    assert(0<=n&&n<(int)fac.size());
    assert(0<=c&&c<(int)inv_fac.size());
    assert(0<=n-c&&n-c<(int)inv_fac.size());
    return (((fac[n]*inv_fac[c])%MOD)*inv_fac[n-c])%MOD;
}

int main(){
    int i,j;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    fac=vector<ll>(a+b+c+d+1);
    inv_fac=vector<ll>(a+b+c+d+1);
    ll ans=0;
    fac[0]=1;
    rep(i,a+b+c+d)fac[i+1]=(fac[i]*(i+1))%MOD;
    inv_fac[a+b+c+d]=power(fac[a+b+c+d],MOD-2);
    for(i=a+b+c+d-1;i>=0;i--)inv_fac[i]=(inv_fac[i+1]*(i+1))%MOD;
    rep(i,b+1){
        ll now=comb(a-1+i,i);
        now=(now*comb((b-i+d)+c,c))%MOD;
        ans=(ans+now)%MOD;
    }
    printf("%lld\n",ans);
    return 0;
}