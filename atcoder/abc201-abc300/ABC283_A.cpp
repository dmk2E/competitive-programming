/*アルゴリズムと工夫点(Power/CPU: 1 ms Memory: 3872 KB  Length: 277 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll a,b;

int main(){
    ll ans=1;
    scanf("%lld%lld",&a,&b);
    while(b--)ans*=a;
    printf("%lld\n",ans);
    return 0;
}