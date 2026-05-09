/*アルゴリズムと工夫点(Edge Deletion/CPU: 33 ms Memory: 5268 KB  Length: 703 B)
ワーシャル・フロイド法において，dp[i][j]が求まるのは，k=（経由する最大の頂点番号）となった時である．
その値を求めるのに用いられる値dp[k][i][j]についてk<maxKとなり正しく求めることができる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k,ans=0;
    scanf("%d%d",&n,&m);
    const ll INF=(int)(2e12);
    vector<vector<ll> > adj(n,vector<ll>(n,INF)),dp(n,vector<ll>(n,INF));
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        adj[i][j]=k;
        dp[i][j]=dp[j][i]=k;
    }
    rep(k,n)rep(i,n)rep(j,n)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    rep(i,n)rep(j,i)if(adj[j][i]!=INF){
        rep(k,n)if(dp[j][k]+dp[k][i]<=adj[j][i])break;
        ans+=k<n;
    }
    printf("%d\n",ans);
    return 0;
}