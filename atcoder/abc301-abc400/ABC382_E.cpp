/*アルゴリズムと工夫点(Expansion Packs/CPU: 65 ms Memory: 4020 KB  Length: 746 B)
まず各パックで，x枚レアを入手できる確率分布P(x)を求めておく．
このP(x)は，
dp[i][j]:i枚目まで見た時の，j枚レアがでている確率
とする動的計画法で解ける．
その後，dp[i]=残りi枚の状態からゴールするまでのパック数の期待値
とする動的計画法で解く．
問題は，レアが0枚である確率が0でない時で，
dp[x]=dp[x]*p0+(dp[x-1]*p1+...)->(1-p0)*dp[x]=(...)->dp[x]=(...)/(1-p0)
とすればよい．
※パックをサイコロとみなした双六をとくイメージ
※双六において、自分のマスに戻ってくるような場合は，右辺にその計算式を書き，移項して割り算をすることで求める事ができる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x,p;

int main(){
    int i,j;
    scanf("%d%d",&n,&x);
    vector<double> dp(n+1,0.0),ans(x+1,0.0);
    dp[0]=1.0;
    rep(i,n){
        scanf("%d",&p);
        vector<double> now(n+1,0.0);
        rep(j,n){
            now[j]+=(1.0-p/100.0)*dp[j];
            now[j+1]+=(p/100.0)*dp[j];
        }
        swap(now,dp);
        // rep(j,n+1)printf("%.3f ",dp[j]);puts("");
    }
    rep(i,x){
        for(j=1;j<=n;j++)ans[i+1]+=ans[max(i+1-j,0)]*dp[j];
        ans[i+1]+=1.0;
        ans[i+1]/=(1.0-dp[0]);
    }
    printf("%.7f\n",ans[x]);
    return 0;
}