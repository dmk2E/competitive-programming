/*アルゴリズムと工夫点(Three Cards/CPU: 8 ms Memory: 3864 KB  Length: 306 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j,ans=0;
    scanf("%d%d",&n,&k);
    rep(i,n)rep(j,n)if(1<=k-i-j-2&&k-i-j-2<=n)ans++;
    printf("%d\n",ans);
    return 0;
}