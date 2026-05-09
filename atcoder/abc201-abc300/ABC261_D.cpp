/*アルゴリズムと工夫点(Flipping and Bonus/CPU: 43 ms Memory: 4000 KB  Length: 990 B)
動的計画法で解けるが，まだその状態に至っていない段階で，その状態からの状態遷移を行うことができないから，その状態が有効ではないと判断するための定数を用意しておくと良い．
※初見4完!
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d",&n,&m);
    vector<int> x(n),c2Y(n+1,0);//回数は0-indexedで，カウンタは1-indexedで
    rep(i,n)scanf("%d",&x[i]);
    while(m--){
        scanf("%d%d",&i,&j);
        c2Y[i]=j;
    }
    const int NIL=-1;
    vector<ll> dp(n+1,NIL);
    auto show=[&]()->void{
        int i;
        rep(i,n+1)printf("%lld ",dp[i]);puts("");
    };
    dp[0]=0;
    rep(i,n){
        //show();
        vector<ll> now=dp;
        rep(j,n){
            if(dp[j]!=NIL){
                now[j+1]=max(dp[j]+x[i]+c2Y[j+1],now[j+1]);
                now[0]=max(dp[j]+c2Y[0],now[0]);
            }
        }
        swap(now,dp);
    }
    //show();
    rep(i,n+1)ans=max(ans,dp[i]);
    printf("%lld\n",ans);
    return 0;
}