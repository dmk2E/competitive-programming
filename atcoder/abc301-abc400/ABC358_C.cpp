/*アルゴリズムと工夫点(Popcorn/CPU: 1 ms Memory: 3912 KB  Length: 811 B)
dp[i][j]:1~i番目の品物の中から選んだ時，jの状態となる時の最小のコスト
という動的計画法で解く．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 10
#define MAX_M 10
#define NIL 10000
using namespace std;

int n,m,s[MAX_N],dp[MAX_N+1][1<<MAX_M]={0};

int main(){
    int i,j,tmp=0;
    char c;
    scanf("%d%d",&n,&m);
    rep(i,n){
        getchar();
        tmp=0;
        rep(j,m){
            tmp*=2;
            tmp+=(getchar()=='o'?1:0);
        }
        //printf("%d\n",tmp);
        s[i]=tmp;
    }
    rep(i,n+1){
        rep(j,1<<m)
            dp[i][j]=NIL;
    }
    dp[0][0]=0;
    for(i=0;i<n;i++){
        rep(j,1<<m){
            dp[i+1][j]=dp[i+1][j]>dp[i][j]?dp[i][j]:dp[i+1][j];
            dp[i+1][j|s[i]]=dp[i+1][j|s[i]]>dp[i][j]+1?dp[i][j]+1:dp[i+1][j|s[i]];
        }
    }
    printf("%d\n",dp[n][(1<<m)-1]);
    return 0;
}