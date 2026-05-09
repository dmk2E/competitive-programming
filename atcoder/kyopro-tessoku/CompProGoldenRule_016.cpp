/*アルゴリズムと工夫点(Dungeon 1/CPU: 16 ms Memory: 4564 KB  Length: 567 B)
動的計画法の練習問題．
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
    vector<int> a(n-1),b(n-2);
    rep(i,n-1)scanf("%d",&a[i]);
    rep(i,n-2)scanf("%d",&b[i]);
    const int INF=(int)(1e9);
    vector<int> dp(n,INF);
    dp[0]=0;
    rep(i,n-1){
        if(dp[i+1]>dp[i]+a[i])dp[i+1]=dp[i]+a[i];
        if(i+2<n&&dp[i+2]>dp[i]+b[i])dp[i+2]=dp[i]+b[i];
    }
    printf("%d\n",dp[n-1]);
    return 0;
}