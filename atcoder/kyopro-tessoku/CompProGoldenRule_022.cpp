/*アルゴリズムと工夫点(Sugoroku/CPU: 22 ms Memory: 9072 KB  Length: 769 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<P> > adj(n);
    rep(i,n-1){
        scanf("%d",&j);
        adj[i].push_back(P(j-1,100));
    }
    rep(i,n-1){
        scanf("%d",&j);
        adj[i].push_back(P(j-1,150));
    }
    const int NIL=-(int)(1e9);
    vector<int> dp(n,NIL);
    dp[0]=0;
    rep(i,n-1){
        if(dp[i]==NIL)continue;
        rep(j,adj[i].size()){
            dp[adj[i][j].first]=max(dp[adj[i][j].first],dp[i]+adj[i][j].second);
        }
    }
    printf("%d\n",dp[n-1]);
    return 0;
}