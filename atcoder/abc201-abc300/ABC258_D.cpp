/*アルゴリズムと工夫点(Trophy/CPU: 41 ms Memory: 4856 KB  Length: 593 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_B (ll)(1e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x;

int main(){
    int i,j,max_stage,min_b=MAX_B+1;
    ll sum=0,ans=(ll)(3e18);
    scanf("%d%d",&n,&x);
    vector<int> a(n),b(n);
    rep(i,n)scanf("%d%d",&a[i],&b[i]);
    max_stage=min(n,x);
    rep(i,max_stage){
        sum+=a[i]+b[i];
        min_b=min(min_b,b[i]);
        ans=min(ans,sum+((ll)min_b*(x-i-1)));
    }
    printf("%lld\n",ans);
    return 0;
}