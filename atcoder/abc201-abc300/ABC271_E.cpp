/*アルゴリズムと工夫点(Subsequence Path/CPU: 62 ms Memory: 8056 KB  Length: 918 B)
ベルマンフォード法における，O(M)の処理を，O(1)にしたような処理をすればよい．
in-place DP とも呼ばれ，値の遷移が定数回しかないことを利用し，一次元配列のDPテーブルを使いまわす実装をする．
※部分文字列の条件を満たすかの判定は，「今現在，元の文字列の何番目か」を記録すれば十分．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct Edge{
    int from,to,cost;

    Edge(int ffrom=0,int tto=0,int ccost=0):from(ffrom),to(tto),cost(ccost){}    
}E;

int n,m,k;

int main(){
    int i,j,ii;
    scanf("%d%d%d",&n,&m,&k);
    vector<E> edge(m);
    vector<int> e(k);
    rep(i,m){
        scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].cost);
        edge[i].from--;edge[i].to--;
    }
    rep(i,k){
        scanf("%d",&e[i]);
        e[i]--;
    }
    const ll INF=(ll)(1e15);
    vector<ll> dp(n,INF);
    dp[0]=0;
    rep(i,k){
        dp[edge[e[i]].to]=min(dp[edge[e[i]].to],dp[edge[e[i]].from]+edge[e[i]].cost);
        //rep(j,n)printf("%lld ",dp[j]==INF?-1:dp[j]);puts("");
    }
    printf("%lld\n",dp[n-1]==INF?-1:dp[n-1]);
    return 0;
}