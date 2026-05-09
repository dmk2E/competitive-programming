/*アルゴリズムと工夫点(Block Game/CPU: 11 ms Memory: 19120 KB  Length: 883 B)
残っているブロックの状態を[i,j)という形で表す時，あり得る状態数はN*Nより小さくなる．
よって，dp[i][j]:ブロックの状態が[i,j)の時の最大点数
とする動的計画法で解ける．最悪計算量は O(N^2)<10^7 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> p(n),a(n);
    rep(i,n){
        scanf("%d%d",&p[i],&a[i]);
        p[i]--;
    }
    const int NIL=-(int)(1e9);
    vector<vector<int> > dp(n+1,vector<int>(n+1,NIL));//[i,j)
    dp[0][n]=0;
    rep(i,n){
        for(j=n;i<j;j--){
            //printf("[%d,%d)\n",i,j);
            dp[i+1][j]=max(dp[i+1][j],dp[i][j]+((i<=p[i]&&p[i]<j)?a[i]:0));
            dp[i][j-1]=max(dp[i][j-1],dp[i][j]+((i<=p[j-1]&&p[j-1]<j)?a[j-1]:0));
            //printf("dp[%d,%d)=%d\n",i+1,j,dp[i+1][j]);printf("dp[%d,%d)=%d\n",i,j-1,dp[i][j-1]);
        }
    }
    j=NIL;
    rep(i,n+1)if(j<dp[i][i])j=dp[i][i];
    printf("%d\n",j);
    return 0;
}