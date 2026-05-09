/*アルゴリズムと工夫点(Warp/CPU: 1625 ms Memory: 9624 KB  Length: 959 B)
移動方法がa,b,cの3通りで表した時，a,b,cそれぞれの移動を行った回数が同じであれば，過程はどうあれ同じ座標に行き着く．
また，a+b+c=Nであり，0<=a,b,c<=N だから，最悪計算量は，O(N^(3)*(log2(N^(2))+log2(M)))<10^8 となり間に合う．
*/
#include<iostream>
#include<map>
#include<set>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll,ll> P;

int n,m;

int main(){
    int i,j;
    const int D=3;
    ll y,x;
    ll dy[3],dx[3];
    scanf("%d%d",&n,&m);
    rep(i,D)scanf("%lld%lld",&dx[i],&dy[i]);
    set<P> obs;
    while(m--){
        scanf("%d%d",&i,&j);
        obs.insert(P(i,j));
    }
    map<P,int> dp;
    dp[P(0,0)]=1;
    while(n--){
        map<P,int> now;
        for(auto p:dp){
            rep(i,D){
                x=p.first.first+dx[i];
                y=p.first.second+dy[i];
                if(obs.find(P(x,y))==obs.end())now[P(x,y)]=(now[P(x,y)]+p.second)%MOD;
            }
        }
        swap(dp,now);
        //printf("n:%d\n",n);
    }
    i=0;
    for(auto p:dp)i=(i+p.second)%MOD;
    printf("%d\n",i);
    return 0;
}