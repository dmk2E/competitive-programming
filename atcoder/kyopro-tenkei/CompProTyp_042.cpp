/*アルゴリズムと工夫点(Multiple of 9/CPU: 5 ms Memory: 4224 KB  Length: 477 B)
「倍数の性質を覚えておく．」
また，動的計画法の状態の遷移において，数字の先頭桁の数字で状態を場合分ける方法があることを覚えておく．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_K (int)(1e5)
#define MOD ((int)(1e9)+7)
using namespace std;

int k,dp[MAX_K+1];

int main(){
    int i,j;
    scanf("%d",&k);
    if(k%9>0)
        printf("%d\n",0);
    else{
        dp[0]=1;
        for(i=1;i<=k;i++){
            dp[i]=0;
            for(j=1;j<=9&&i-j>=0;j++)dp[i]=(int)(((long long)dp[i]+dp[i-j])%MOD);
        }
        printf("%d\n",dp[k]);
    }
    return 0;
}