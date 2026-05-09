/*アルゴリズムと工夫点(Get Many Stickers/CPU: 85 ms Memory: 6520 KB  Length: 719 B)
貪欲法で解く．
交換後のビンの本数は大きい方が良い．つまり，「A-B」の値が小さい順に使っていくと良い．
ただし，交換前の本数はA以上である必要があることに注意．
最悪計算量は，O(M*log2(M))<10^7 となり高速．
※貪欲法は苦手であるため，解けるようになりたい．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll,ll> P;//(B-A,A)

ll n;
int m;

int main(){
    int i,j;
    ll ans=0;
    scanf("%lld%d",&n,&m);
    vector<P> ipt(m);
    rep(i,m){
        scanf("%lld%lld",&ipt[i].second,&ipt[i].first);
        ipt[i].first-=ipt[i].second;
    }
    sort(ipt.rbegin(),ipt.rend());
    rep(i,m){
        if(n>=ipt[i].second){
            ll cnt=(n-ipt[i].second)/(-ipt[i].first)+1;
            ans+=cnt;
            n+=cnt*ipt[i].first;
        }
    }
    printf("%lld\n",ans);
    return 0;
}