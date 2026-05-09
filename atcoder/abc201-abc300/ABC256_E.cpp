/*アルゴリズムと工夫点(Takahashi's Anguish/CPU: 80 ms Memory: 18468 KB  Length: 1647 B)
問題をグラフとみなすと，サイクル内で，最小の辺を消去すればよい問題になる．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_C (int)(1e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d",&n);
    const int NIL=-1;
    vector<int> x(n),c(n),color(n,NIL),indeg(n,0);
    vector<vector<int> > adj(n);
    rep(i,n){
        scanf("%d",&x[i]);
        x[i]--;
        indeg[x[i]]++;
        adj[i].push_back(x[i]);
        adj[x[i]].push_back(i);
    }
    rep(i,n)scanf("%d",&c[i]);
    auto bfs=[&](int now,int id)->vector<int>{
        int i;
        vector<int> ans;
        queue<int> que;
        color[now]=id;
        que.push(now);
        ans.push_back(now);
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size())if(color[adj[now][i]]==NIL){
                color[adj[now][i]]=id;
                que.push(adj[now][i]);
                ans.push_back(adj[now][i]);
            }
        }
        return ans;
    };
    auto tSort=[&](vector<int> nodes)->int{
        int i,j,ans=MAX_C+1;
        queue<int> que;
        rep(i,nodes.size())if(indeg[nodes[i]]==0)que.push(nodes[i]);
        while(que.size()){
            i=que.front();que.pop();
            indeg[x[i]]--;
            if(indeg[x[i]]==0)que.push(x[i]);
        }
        rep(i,nodes.size())if(indeg[nodes[i]]>0)ans=min(ans,c[nodes[i]]);
        return (ans==MAX_C+1)?0:ans;
    };
    j=0;
    rep(i,n)if(color[i]==NIL)ans+=tSort(bfs(i,j++));
    printf("%lld\n",ans);
    return 0;
}