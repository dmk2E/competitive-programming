/*アルゴリズムと工夫点(Stair Jump（★3）/CPU: 2 ms Memory: 4244 KB  Length: 404 B)
動的計画法で初見ACできた．
※キーワード「」
*/
#include<iostream>
#define MAX_N (int)(1e5)
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD ((int)(1e9)+7)
using namespace std;

int n,l,dp[MAX_N+1]={0};

int main(){
    int i,j;
    scanf("%d%d",&n,&l);
    dp[0]=1;
    rep(i,n){
        dp[i+1]=(dp[i+1]+dp[i])%MOD;
        if(l!=1&&i+l<=n)
            dp[i+l]=(dp[i+l]+dp[i])%MOD;
    }
    printf("%d\n",dp[i]);
    return 0;
}