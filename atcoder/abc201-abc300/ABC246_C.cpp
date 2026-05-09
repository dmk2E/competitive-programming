/*アルゴリズムと工夫点(Coupon/CPU: 36 ms Memory: 4140 KB  Length: 938 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll k,x;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%lld%lld",&n,&k,&x);
    vector<int> a(n);
    rep(i,n){
        scanf("%d",&a[i]);
        ans+=a[i];
    }
    rep(i,n){
        if(k>=(a[i]/x)){
            ans-=(a[i]/x)*x;
            k-=(a[i]/x);
            a[i]%=x;
        }else{
            a[i]-=k*x;
            ans-=k*x;
            k=0;
            break;
        }
    }
    // rep(i,n)printf("%d ",a[i]);puts("");
    if(k>0){
        sort(a.rbegin(),a.rend());
        rep(i,n){
            ans-=a[i];
            a[i]=0;
            k--;
            if(k==0)break;
        }
    }
    // rep(i,n)printf("%d ",a[i]);puts("");
    printf("%lld\n",ans);
    return 0;
}