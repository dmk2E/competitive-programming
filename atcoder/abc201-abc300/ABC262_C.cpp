/*アルゴリズムと工夫点(Min Max Pair/CPU: 39 ms Memory: 5432 KB  Length: 470 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    j=0;
    rep(i,n){
        if(a[i]==i+1)j++;
        else ans+=(i<a[i]-1&&a[a[i]-1]==i+1);
    }
    printf("%lld\n",ans+(ll)j*(j-1)/2);
    return 0;
}