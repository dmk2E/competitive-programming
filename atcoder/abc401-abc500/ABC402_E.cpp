/*アルゴリズムと工夫点(Payment Required/CPU: 17 ms Memory: 14060 KB  Length: 715 B)
従来の期待値DPと同様に，"その状態からゴールの状態に至るまでの期待値の最大値"をDPしていくイメージ．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&x);
    vector<int> s(n),c(n);
    vector<double> p(n);
    rep(i,n){
        scanf("%d%d%lf",&s[i],&c[i],&p[i]);
        p[i]=p[i]/100.0;
    }
    const double NIL=0;
    vector<vector<double> > dp(x+1,vector<double>(1<<n,NIL));
    rep(i,x+1)rep(j,1<<n){
        rep(k,n)if((((j>>k)&1)==0)&&c[k]<=i){
            dp[i][j]=max(dp[i][j],(dp[i-c[k]][j|(1<<k)]+s[k])*p[k]+dp[i-c[k]][j]*(1-p[k]));
        }
    }
    printf("%.7f\n",dp[x][0]);
    return 0;
}