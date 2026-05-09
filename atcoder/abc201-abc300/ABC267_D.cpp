/*アルゴリズムと工夫点(Index × A(Not Continuous ver.)/CPU: 4 ms Memory: 3944 KB  Length: 551 B)
dp[i][j]:A[0,i)でj個選んだ時の，部分列の最大値
とする動的計画法で解ける．
最悪計算量は O(N*M)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    const ll NIL=(ll)(-1e18);
    scanf("%d%d",&n,&m);
    ll a;
    vector<ll> dp(m+1,NIL);
    dp[0]=0;//A[0,i)からj個選んだ
    rep(i,n){
        scanf("%lld",&a);
        vector<ll> now=dp;
        rep(j,m)if(dp[j]!=NIL)now[j+1]=max(now[j+1],dp[j]+(j+1)*a);
        swap(dp,now);
    }
    printf("%lld\n",dp[m]);
    return 0;
}