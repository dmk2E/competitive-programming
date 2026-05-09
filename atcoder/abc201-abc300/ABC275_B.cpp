/*アルゴリズムと工夫点(ABC-DEF/CPU: 1 ms Memory: 3908 KB  Length: 380 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll a,b,c,d,e,f;

int main(){
    scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e,&f);
    printf("%lld\n",(MOD+(((((a%MOD)*(b%MOD))%MOD)*(c%MOD))%MOD-((((d%MOD)*(e%MOD))%MOD)*(f%MOD))%MOD))%MOD);
    return 0;
}