/*アルゴリズムと工夫点(Dice Product（★3）/CPU: 1 ms Memory: 3856 KB  Length: 405 B)
各目の総和の積が答えになる．高校数学Aでやった内容．
※因数分解をしよう,複雑な問題で小さなケースを考えるのは重要な典型考察テクニック
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD (int)((1e9)+7)
using namespace std;
typedef long long ll;

int n;

int main(){
    int i,j,a;
    ll ans=1,tmp=0;
    scanf("%d",&n);
    rep(i,n){
        tmp=0;
        rep(j,6){
            scanf("%d",&a);
            tmp+=a;
        }
        ans=(ans*tmp)%MOD;
    }
    printf("%lld\n",ans);
    return 0;
}