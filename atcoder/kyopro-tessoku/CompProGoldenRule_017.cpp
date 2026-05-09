/*アルゴリズムと工夫点(Dungeon 2/CPU: 16 ms Memory: 5548 KB  Length: 915 B)
DP復元の練習問題．
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
    vector<int> dp(n,INF),par(n,INF);
    dp[0]=0;
    rep(i,n-1){
        if(dp[i+1]>dp[i]+a[i]){
            dp[i+1]=dp[i]+a[i];
            par[i+1]=i;
        }
        if(i+2<n&&dp[i+2]>dp[i]+b[i]){
            dp[i+2]=dp[i]+b[i];
            par[i+2]=i;
        }
    }
    vector<int> ans;
    j=n-1;
    ans.push_back(j);
    while(par[j]!=INF){
        j=par[j];
        ans.push_back(j);
    }
    printf("%d\n",(int)ans.size());rep(i,ans.size()-1)printf("%d ",ans[ans.size()-1-i]+1);printf("%d\n",ans[ans.size()-1-i]+1);
    return 0;
}