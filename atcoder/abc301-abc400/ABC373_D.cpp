/*アルゴリズムと工夫点(Hidden Weights/CPU: 116 ms Memory: 31736 KB  Length: 1291 B)
連結成分部分は，頂点の値が一つ決まると連鎖的に決まる．
通常のDFS等では，有向グラフ上だと，ただ辺で繋がっているだけでは任意の頂点から頂点への移動が自由にできず，連結ではない可能性がある．
そこで，ある1つの辺を繋ぐ際に逆向きの辺を重みの符号を逆にして繋ぐようにすることで，この問題を解決できる．
最悪計算量は O(N+M)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct data{
    int u,v,w;

    data(int uu=0,int vv=0,int ww=0):u(uu),v(vv),w(ww){}
}Data;

typedef pair<int,int> p;

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<vector<p> > adj(n,vector<p>(0));
    //vector<Data> ipt;
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        //ipt.push_back(Data(i,j,k));
        adj[i].push_back(p(j,k));
        adj[j].push_back(p(i,-k));
    }
    vector<bool> visited(n);
    vector<ll> ans(n);
    auto dfs=[&](auto& f,int now)->void{
        int i;
        rep(i,adj[now].size()){
            if(visited[adj[now][i].first]==false){
                visited[adj[now][i].first]=true;
                ans[adj[now][i].first]=ans[now]+adj[now][i].second;
                f(f,adj[now][i].first);
            }
        }
    };
    rep(i,n)if(visited[i]==false){
        visited[i]=true;
        ans[i]=0;
        dfs(dfs,i);
    }
    //rep(i,ipt.size()){if(ans[ipt[i].v]-ans[ipt[i].u]!=(ll)ipt[i].w){puts("false");}}
    rep(i,n-1)printf("%lld ",ans[i]);
    printf("%lld\n",ans[i]);
    return 0;
}