/*アルゴリズムと工夫点(Arithmetic Number/CPU: 1 ms Memory: 3948 KB  Length: 695 B)
等差数の数自体が，(桁数)*(最初の値)*(公差のとり得る範囲)=18*9*10<10^4 となり少ないため，全探索ができる．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_KETA 18
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll x;
const ll INF=(ll)(1e18);

ll calAN(int n,int f,int r){//桁数n,最初の値，公差
    if(0>f+r*(n-1)||f+r*(n-1)>=10)return INF;
    ll ans=0;
    while(n--){
        ans*=10;
        ans+=f;
        f+=r;
    }
    return ans;
}

int main(){
    int i,j,k;
    ll ans=INF,tmp;
    scanf("%lld",&x);
    for(i=1;i<=MAX_KETA;i++)rep(j,9)rep(k,10){
        if((tmp=calAN(i,j+1,k))>=x&&tmp<ans)ans=tmp;
        if((tmp=calAN(i,j+1,-k))>=x&&tmp<ans)ans=tmp;
    }
    printf("%lld\n",ans);
    return 0;
}