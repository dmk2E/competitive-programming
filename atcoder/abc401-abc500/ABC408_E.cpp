/*アルゴリズムと工夫点(Minimum OR Path/CPU: 637 ms Memory: 27096 KB  Length: 1056 B)
「ビット毎に考える」のは典型だが，「各ビットを0にできるか」という判定をDFSで行い，前から決めていく．
最悪計算量は，O((N+M)*max(wi))<10^7 となり高速．
※「単純パス」の全列挙は，O(N+M)では不可能．しかし，「ある辺のみを用いて始点から終点まで到達可能か」という問題はO(N+M)で可能．
※↑の発想が重要．
※あるビットxが1になるしかない場合，始点から終点に着くまでに通過する辺の重みのビットxが0でも1でもどっちでも良いことに注意．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX 30
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;//(id,cost)

int n,m;

int main(){
    int i,j,k,ans,now,lgh;
    scanf("%d%d",&n,&m);
    vector<vector<P> > adj(n);
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        adj[i].push_back(P(j,k));
        adj[j].push_back(P(i,k));
    }
    lgh=0;
    ans=(1<<MAX)-1;
    vector<bool> vis;
    auto dfs=[&](auto& func,int now)->bool{
        int i;
        vis[now]=true;
        if(now==n-1)return true;
        rep(i,adj[now].size()){
            if(vis[adj[now][i].first]==false&&(adj[now][i].second==(adj[now][i].second&(ans^lgh))))if(func(func,adj[now][i].first))return true;
        }
        return false;
    };
    for(i=MAX-1;i>=0;i--){
        lgh=(1<<i);
        vis=vector<bool>(n,false);
        if(dfs(dfs,0))ans^=(1<<i);
    }
    printf("%d\n",ans);
    return 0;
}