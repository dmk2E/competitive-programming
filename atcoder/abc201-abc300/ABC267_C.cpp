/*アルゴリズムと工夫点(Index × A(Continuous ver.)/CPU: 19 ms Memory: 4020 KB  Length: 718 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    const ll NIL=(ll)(-(1e18));
    ll sum=0,nSum=0,mx=NIL;
    scanf("%d%d",&n,&m);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    rep(i,m){
        sum+=((ll)i+1)*a[i];
        nSum+=a[i];
    }
    for(j=0;i<n;i++,j++){//[j,i)
        //printf("[%d,%d)=%lld\n",j,i,sum);
        mx=max(mx,sum);
        sum+=(ll)m*a[i];
        sum-=nSum;
        nSum-=a[j];
        nSum+=a[i];
    }
    //printf("[%d,%d)=%lld\n",j,i,sum);
    mx=max(mx,sum);
    printf("%lld\n",mx);
    return 0;
}