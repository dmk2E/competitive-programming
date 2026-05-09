/*アルゴリズムと工夫点(±1 Operation 2/CPU: 94 ms Memory: 5888 KB  Length: 676 B)
最悪計算量 O((N+Q)*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    ll ans;
    scanf("%d%d",&n,&q);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    vector<ll> sum_a(n+1,0);
    rep(i,n)sum_a[i+1]=sum_a[i]+a[i];
    while(q--){
        scanf("%d",&i);
        ans=0;
        j=upper_bound(a.begin(),a.end(),i)-a.begin();
        ans+=(ll)j*i-sum_a[j];
        ans+=sum_a[n]-sum_a[j]-(ll)(n-j)*i;
        printf("%lld\n",ans);
    }
    return 0;
}