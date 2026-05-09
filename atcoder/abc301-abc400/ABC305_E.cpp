/*アルゴリズムと工夫点(Art Gallery on Graph/CPU: 145 ms Memory: 18424 KB  Length: 1257 B)
優先度付きキュー+多始点BFSで解く．
警備員のいる頂点を始点とする多始点BFSをして，解を求める．
ただし各頂点に到達時，体力が最大の警備員を記録していくこと．
最悪計算量は，O((N+M)*log2(N+M))<10^7 となり高速．
※初見AC．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;//(体力,頂点番号)

int n,m,k;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&m,&k);
    vector<vector<int> > adj(n);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    auto bfs=[&]()->void{
        priority_queue<P> PQ;
        vector<bool> vis(n,false);
        P now;
        while(k--){
            scanf("%d%d",&i,&j);
            PQ.push(P(j,i-1));
        }
        while(PQ.size()){
            do{
                now=PQ.top();PQ.pop();
            }while(PQ.size()&&vis[now.second]);
            if(vis[now.second])break;
            vis[now.second]=true;
            if(now.first<1)continue;
            for(auto x:adj[now.second])if(vis[x]==false)PQ.push(P(now.first-1,x));
        }
        int i;
        vector<int> ans;
        rep(i,n)if(vis[i])ans.push_back(i+1);
        printf("%ld\n",ans.size());rep(i,ans.size()-1)printf("%d ",ans[i]);printf("%d\n",ans[i]);
    };
    bfs();
    return 0;
}