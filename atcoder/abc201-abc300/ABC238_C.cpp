/*アルゴリズムと工夫点(digitnum/CPU: 1 ms Memory: 3852 KB  Length: 641 B)
f(N)=N-floor(log10(N))+1 より，Σf(N)=Σ(1<=k<=N)k-Σ(1<=k<=N)floor(log10(k))+N
Σ(1<=k<=N)floor(log10(k)) は直接線形的に求めればよいから，最悪計算量は O(log2(MOD))となり十分高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

ll power(ll x,ll a){
    if(a==0)return 1;
    x%=MOD;
    ll res=power((x*x)%MOD,a/2);
    if(a%2==1)res=(res*x)%MOD;
    return res;
}

int main(){
    int i,j;
    ll f=0,tmp=1;
    scanf("%lld",&n);
    while(n>=tmp*10){
        f=(f+9*(((tmp%MOD)*(tmp%MOD))%MOD))%MOD;
        tmp*=10;
    }
    f=(f+((((n-tmp+1)%MOD)*(tmp%MOD))%MOD))%MOD;
    printf("%lld\n",((MOD+(((n%MOD)*((n+1)%MOD))%MOD)*power(2,MOD-2)-f)%MOD+n%MOD)%MOD);
    return 0;
}