/*アルゴリズムと工夫点(Tree Distance/CPU: 33 ms Memory: 10428 KB  Length: 809 B)
キーワード:「答えへの貢献度を考える」
木上で，その辺を何回通るかが分かればよいから，その頂点を根とする部分木に含まれる頂点の個数を木DPで求めて，解を計算する．
木DP:木のどこかの頂点を根とし，dfsを行い，頂点番号iを根とする部分木に関する何らかの値をdp[i]として保持して，求めたい値を求めていくDP．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(1e5)
using namespace std;

typedef pair<int,int> p;

int n,dp[MAX_N]={0};
vector<p> edge;
vector<int> adj[MAX_N];

int dfs(int root){
    int i;
    dp[root]=1;
    for(i=0;i<adj[root].size();i++){
        if(dp[adj[root][i]]==0)
            dp[root]+=dfs(adj[root][i]);
    }
    return dp[root];
}

int main(){
    int i,j,k;
    long long ans=0;
    scanf("%d",&n);
    rep(i,n-1){
        scanf("%d%d",&j,&k);
        edge.push_back(p(--j,--k));
        adj[j].push_back(k);
        adj[k].push_back(j);
    }
    dfs(0);
    rep(i,n-1){
        j=min(dp[edge[i].first],dp[edge[i].second]);
        ans+=(long long)j*(n-j);
    }
    printf("%lld\n",ans);
    return 0;
}