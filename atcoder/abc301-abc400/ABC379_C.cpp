/*アルゴリズムと工夫点(Sowing Stones/CPU: 58 ms Memory: 6520 KB  Length: 1053 B)
石は右方向にしか移動しないから，次の石があるマス目の手前まで持ってる石で埋める．操作後，2個以上石が残った場合，次の石があるマスに残りの石を移動させればよい．
また，1番目のマスに石がなかったり，石移動の際に個数が足りなければ，その時点で「-1」を出力する．
※重実装の貪欲法の問題だった...
※問題文をよく読むこと!
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,ll> P;

int n,m;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d",&n,&m);
    vector<P> ipt(m);
    rep(i,m)scanf("%d",&ipt[i].first);
    rep(i,m)scanf("%lld",&ipt[i].second);
    sort(ipt.begin(),ipt.end());
    if(ipt[0].first==1){
        i=1;
        j=0;
        while(i<=n&&j+1<m){
            if(ipt[j].second-1<ipt[j+1].first-i-1){
                puts("-1");
                return 0;
            }
            ans+=((ll)ipt[j+1].first-i-1)*(ipt[j+1].first-i)/2;
            ans+=(ipt[j].second-ipt[j+1].first+i)*(ipt[j+1].first-i);
            ipt[j+1].second+=ipt[j].second-ipt[j+1].first+i;
            j++;
            i=ipt[j].first;
        }
        if(n-i==ipt[j].second-1){
            printf("%lld\n",ans+((ll)n-i)*(n-i+1)/2);
            return 0;
        }
    }
    puts("-1");
    return 0;
}