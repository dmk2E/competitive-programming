/*アルゴリズムと工夫点(Combination/CPU: 2 ms Memory: 4356 KB  Length: 570 B)
フェルマーの小定理と繰り返し自乗法を用いれば，逆元を計算可能．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD ((int)(1e9)+7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,r;

ll power(ll a,ll b){
    if(b==0)return 1;
    ll res=power((a%MOD)*(a%MOD),b/2);
    if(b%2==1)res=res*(a%MOD);
    return res%MOD;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&r);
    vector<ll> fac(1,1);
    rep(i,n)fac.push_back((fac[i]*(i+1))%MOD);
    printf("%lld\n",(((fac[n]*power(fac[n-r],MOD-2))%MOD)*power(fac[r],MOD-2))%MOD);
    return 0;
}