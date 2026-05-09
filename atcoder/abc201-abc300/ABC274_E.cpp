/*アルゴリズムと工夫点(Booster/CPU: 401 ms Memory: 48564 KB  Length: 1333 B)
dp[i][j][k]:今まで訪れた都市の集合j，今まで訪れた宝箱の集合kであり，今都市iにいる時の最短時間
とするビットDPで解ける．巡回セールスマン問題の亜種．
最悪計算量はO((N+M+1)*(N+M+1)*2^(N+M+1))<10^8 となり，間に合う．
*/
#include<iostream>
#include<vector>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int popCount(int x){
    int cnt=0;
    while(x>0){
        cnt+=x&1;
        x>>=1;
    }
    return cnt;
}

int main(){
    int i,j,k,ii;
    double ans;
    scanf("%d%d",&n,&m);
    n++;
    vector<int> x(n+m),y(n+m);
    vector<vector<double> > adj(n+m,vector<double>(n+m,0));
    vector<int> two;
    two.push_back(1);
    rep(i,m)two.push_back(two[i]*2);
    x.push_back(0);y.push_back(0);
    rep(i,n+m-1)scanf("%d%d",&x[i+1],&y[i+1]);
    rep(i,n+m)rep(j,n+m)adj[i][j]=hypot((double)x[i]-x[j],y[i]-y[j]);
    const double INF=1e10;
    vector<vector<vector<double> > > dp(n+m,vector<vector<double> >(1<<n,vector<double>(1<<m,INF)));
    dp[0][0][0]=0;
    rep(k,1<<m)rep(j,1<<n)rep(i,n+m){
        rep(ii,n+m){
            if(ii<n){
                dp[ii][j|(1<<ii)][k]=min(dp[ii][j|(1<<ii)][k],dp[i][j][k]+adj[i][ii]/two[popCount(k)]);
            }else{
                dp[ii][j][k|(1<<(ii-n))]=min(dp[ii][j][k|(1<<(ii-n))],dp[i][j][k]+adj[i][ii]/two[popCount(k)]);
            }
        }
    }
    ans=INF;
    rep(k,1<<m)ans=min(ans,dp[0][(1<<n)-1][k]);
    printf("%.7f\n",ans);
    return 0;
}