/*アルゴリズムと工夫点(Just one/CPU: 77 ms Memory: 16728 KB  Length: 1391 B)
<i>実験により，N=Mでないと条件を満たすことはできないことに気づく．
<ii>根付き木(M=N-1)に1本辺を追加すると，サイクル1つに対し，木がくっついたものになる．
<iii>向き付けはサイクル部分しか自由度がなく，2となる．従って解は2^(連結成分数)となる．
※グラフに関連する問題は，連結成分ごとに独立に考えることができることがある．
※与えられた条件を満たすためのグラフ条件として着目すべきは，頂点数や辺の数がある．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,m;

int main(){
    int i,j,k=0;
    ll ans=1;
    scanf("%d%d",&n,&m);
    vector<vector<p> > adj(n,vector<p>(0));
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(p(j,k));
        adj[j].push_back(p(i,k));
        k++;
    }
    vector<bool> edge(k,false),visited(n,false);
    auto bfs=[&](int now)->bool{
        int i,nn=1,mm=0;
        visited[now]=true;
        queue<int> que;
        que.push(now);
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(visited[adj[now][i].first]==false){
                    visited[adj[now][i].first]=true;
                    nn++;
                    que.push(adj[now][i].first);
                }
                if(edge[adj[now][i].second]==false){
                    edge[adj[now][i].second]=true;
                    mm++;
                }
            }
        }
        return nn==mm;
    };
    rep(i,n)
        if(visited[i]==false){
            if(bfs(i))ans=(ans*2)%MOD;
            else break;
        }
    printf("%lld\n",i==n?ans:0);
    return 0;
}