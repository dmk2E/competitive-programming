/*アルゴリズムと工夫点(Integer Sequence Fair/CPU:  ms Memory:  KB  Length:  B)
フェルマーの小定理:x^(p-1)≡1(mod p) (xとpは互いに素)
を利用すると，求めたい値M^(K^N)≡M^(q*(p-1)+r)≡(M^(p-1))^(q)*M^(r)≡M^(r)
が成立する．よって，繰り返し二乗法を用いて高速に値を求めることができる．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n,k,m;

ll gcd(ll a,ll b){
    return b==0?a:gcd(b,a%b);
}

ll power(ll x,ll a,int mod){
    if(a==0)return 1;
    ll res=power(((x%mod)*(x%mod))%mod,a/2,mod);
    if(a%2==1)res=(res*(x%mod))%mod;
    return res;
}

int main(){
    int i,j;
    scanf("%lld%lld%lld",&n,&k,&m);
    printf("%lld\n",gcd(m,MOD)==1LL?power(m,power(k,n,MOD-1),MOD):0LL);
    return 0;
}