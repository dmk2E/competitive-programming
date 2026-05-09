/*アルゴリズムと工夫点(Counting Numbers（★3）/CPU: 2 ms Memory: 3888 KB  Length: 891 B)
制約が10^(18)と大きい場合，処理の都合上10^(19)の値まで扱う可能性があるから，unsigned long long型の変数を用いること．
※部分問題に分割する/数列の和の公式
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD (int)((1e9)+7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull l,r;

ll power(ll x,int a){
    if(a==0)return 1;
    x%=MOD;
    ll res=power((x*x)%MOD,a/2);
    if(a%2==1)res=(res*x)%MOD;
    return res;
}

ull cal(ll l,ll r){
    r%=MOD;
    return (ull)((((MOD+((r*(r+1))%MOD)-(((l%MOD)*((MOD+l-1)%MOD))%MOD))%MOD)*power(2,MOD-2))%MOD);
}

int main(){
    int i,j;
    ull tmp,ans=0;
    scanf("%llu%llu",&l,&r);
    tmp=l;
    i=1;
    while(tmp>=10){tmp/=10;i++;}
    tmp=1;
    rep(j,i)tmp*=10;
    while(l<=r){
        //printf("[%llu,%llu(%llu)]\n",l,min(tmp-1,r),tmp);
        ans=(ans+(((ull)i*cal((ll)l,(ll)min(tmp-1,r)))%MOD))%MOD;
        l=min(tmp-1,r)+1;
        i++;
        tmp*=10;
    }
    printf("%llu\n",ans);
    return 0;
}