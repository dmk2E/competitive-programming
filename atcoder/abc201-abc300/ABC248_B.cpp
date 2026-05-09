/*アルゴリズムと工夫点(Slimes/CPU: 1 ms Memory: 3880 KB  Length: 336 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll a,b,k;

int main(){
    int ans=0;
    scanf("%lld%lld%lld",&a,&b,&k);
    while(a<b){
        ans++;
        a*=k;
    }
    printf("%d\n",ans);
    return 0;
}