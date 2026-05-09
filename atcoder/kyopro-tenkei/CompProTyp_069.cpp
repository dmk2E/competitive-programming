/*アルゴリズムと工夫点(Colorful Blocks 2（★3）/CPU: 2 ms Memory: 3912 KB  Length: 574 B)
型のオーバーフローに気づけず，2WA...気を付けたい．
※キーワードは，a^(b)mod m は繰り返し二乗法
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD (int)((1e9)+7)
using namespace std;
typedef long long ll;

ll n,k;

ll power(ll x,ll a){
    if(a==0)return 1;
    ll res=power((x*x)%MOD,a/2);
    if(a%2==1)res=(res*x)%MOD;
    return res;
}

int main(){
    int i,j;
    ll ans=1;
    scanf("%lld%lld",&n,&k);
    if(k==1&&n==1)
        puts("1");
    else if(k==2&&n<=2)
        puts("2");
    else if(k>=3)
        printf("%lld\n",n>=2?(((k*(k-1))%MOD)*power(k-2,n-2))%MOD:k);
    else
        puts("0");
    return 0;
}