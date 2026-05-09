/*アルゴリズムと工夫点(Roulettes/CPU: 3 ms Memory: 3988 KB  Length: 922 B)
期待値DPで解く．
dp[x] = 残りxポイントである時，Mポイント得るまでにかかる最小の費用
最悪計算量は，O(N*M*maxP)<10^7 となり高速．
※ 期待値計算では，「その状態に至ったら，そのコストだけかかる」と考えて良い
※ 双六ゲームと捉え，ゴールから解を求めていく．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_S 100
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<vector<int> > rlt_to_cnt(n,vector<int>(MAX_S+1,0));
    vector<int> c(n),p(n);
    rep(i,n){
        scanf("%d%d",&c[i],&p[i]);
        rep(j,p[i]){
            int s;
            scanf("%d",&s);
            rlt_to_cnt[i][s]++;
        }
    }
    const double INF=1e9;
    vector<double> dp(m+1,INF);
    dp[0]=0.0;
    for(i=1;i<=m;i++){
        rep(j,n){
            double tmp=0.0;
            for(k=1;k<=MAX_S;k++)tmp+=(double)rlt_to_cnt[j][k]*dp[max(0,i-k)]/p[j];
            tmp+=c[j];
            dp[i]=min(dp[i],tmp/(1.0-(double)rlt_to_cnt[j][0]/p[j]));
        }
    }
    printf("%.10f\n",dp[m]);
    return 0;
}