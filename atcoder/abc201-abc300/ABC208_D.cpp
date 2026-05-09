/*アルゴリズムと工夫点(Shortest Path Queries 2/CPU: 96 ms Memory: 4528 KB  Length: 671 B)
ワーシャル・フロイド法を知っていれば解ける問題.最悪計算量O(n^3)となる,全点対最短経路問題を解くアルゴリズムで,ベルマンフォード法と同じく,覚えておく.
※一発ACできた!
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 400
#define INF 400000001
using namespace std;

int n,m,dp[MAX_N][MAX_N];

int main(){
    int i,j,k;
    long long sum=0;
    scanf("%d%d",&n,&m);
    rep(i,n)rep(j,n){if(i==j)dp[i][j]=0;else dp[i][j]=INF;}
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        dp[i][j]=k;
    }
    rep(k,n){
        rep(i,n){
            rep(j,n){
                if(dp[i][j]>dp[i][k]+dp[k][j])
                    dp[i][j]=dp[i][k]+dp[k][j];
                sum+=(dp[i][j]==INF?0:dp[i][j]);
            }
        }
    }
    printf("%lld\n",sum);
    return 0;
}