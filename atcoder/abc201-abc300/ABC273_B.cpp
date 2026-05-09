/*アルゴリズムと工夫点(Broken Rounding/CPU: 1 ms Memory: 3932 KB  Length: 350 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll x;
int k;

int main(){
    int i,j;
    ll ten=1;
    scanf("%lld%d",&x,&k);
    rep(i,k){
        x=((x+5*ten)/(ten*10))*(ten*10);
        ten*=10;
    }
    printf("%lld\n",x);
    return 0;
}