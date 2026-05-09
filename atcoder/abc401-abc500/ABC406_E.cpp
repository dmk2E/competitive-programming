/*アルゴリズムと工夫点(Popcount Sum 3/CPU: 3 ms Memory: 3960 KB  Length: 1237 B)
「i桁目まで決めた時の～」という形で問題を分割するDPを桁DPという．
dp[i][j][k]=上からi桁決めて，N以下が確定したか否か，かつpopcountがkである時の，...
※理解がまだできてない...
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_DIGIT 60
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t,k;
ll n,dp[MAX_DIGIT+1][2][2][MAX_DIGIT+1];

int solve(ll n,int kk){
    int i,j,k,ii,val;
    rep(i,MAX_DIGIT+1)rep(j,2)rep(k,2)rep(ii,MAX_DIGIT)dp[i][j][k][ii]=0;
    dp[MAX_DIGIT][0][0][0]=1;
    n++;
    for(i=MAX_DIGIT-1;i>=0;i--){
        rep(j,2)rep(k,2)rep(ii,MAX_DIGIT){
            ll now=dp[i+1][j][k][ii];
            if(now==0)continue;
            rep(val,2){
                int nxt_k=k,nxt_ii=ii+val;
                if(k==0){
                    if(val<((n>>i)&1))nxt_k=1;
                    if(val>((n>>i)&1))continue;
                }
                if(nxt_ii>kk)continue;
                dp[i][j][nxt_k][nxt_ii]=(dp[i][j][nxt_k][nxt_ii]+now)%MOD;
                if(j==0 && val)dp[i][1][nxt_k][nxt_ii]=(dp[i][1][nxt_k][nxt_ii]+(now*((1LL<<i)%MOD))%MOD)%MOD;
            }
        }
    }
    return dp[0][1][1][kk];
}

int main(){
    int i,j;
    scanf("%d",&t);
    while(t--){
        scanf("%lld%d",&n,&k);
        printf("%d\n",solve(n,k));
    }
    return 0;
}