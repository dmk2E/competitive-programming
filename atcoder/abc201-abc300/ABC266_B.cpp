/*アルゴリズムと工夫点(Modulo Number/CPU: 1 ms Memory: 3928 KB  Length: 271 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define M 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    scanf("%lld",&n);
    printf("%lld\n",n>=0?n%M:(M-((-n)%M))%M);
    return 0;
}