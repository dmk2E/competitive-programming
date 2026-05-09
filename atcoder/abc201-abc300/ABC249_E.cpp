/*アルゴリズムと工夫点(RLE/CPU: 392 ms Memory: 144284 KB  Length: 1428 B)
dp[i][j]:今現在のsの長さがiでtの長さがjである時の場合の数
問題は遷移をしやすいように，文字のブロックで追加していくことを考えること．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,p;

int main(){
    int i,j;
    scanf("%d%d",&n,&p);
    auto f=[](int x)->int{
        int ans=0;
        while(x>0){
            ans++;
            x/=10;
        }
        return ans+1;
    };
    vector<vector<ll> > dp(n+1,vector<ll>(n,0));
    vector<vector<ll> > sum(n+2,vector<ll>(n+1,0));
    for(int w=1;w<=n;w++)dp[w][f(w)]=26;
    const int ten[]={0,1,10,100,1000,10000};
    for(i=1;i<=n;i++){
        rep(j,n){
            // for(int w=1;w<i;w++){
            //     int nj=j-f(w);
            //     if(nj<0)break;
            //     dp[i][j]=(dp[i][j]+(dp[i-w][nj]%p)*25)%p;
            // }
            for(int k=1;k<=4;k++){
                int nj=j-k-1;
                if(nj<0)break;
                int lb=ten[k],ub=ten[k+1];
                ub=min(ub,i);
                if(lb>=ub)continue;
                // for(int w=lb;w<ub;w++){
                //     dp[i][j]=(dp[i][j]+(dp[i-w][nj]*25)%p)%p;
                // }
                dp[i][j]=(dp[i][j]+(((p+sum[i-lb+1][nj]-sum[i-ub+1][nj])%p)*25)%p)%p;
            }
            sum[i][j]=((sum[i-1][j])%p+dp[i-1][j])%p;
        }
    }
    ll ans=0;
    rep(j,n)ans=(ans+dp[n][j])%p;
    printf("%lld\n",ans);
    return 0;
}