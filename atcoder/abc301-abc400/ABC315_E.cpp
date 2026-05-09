/*アルゴリズムと工夫点(Prerequisites/CPU: 175 ms Memory: 28256 KB  Length: 1680 B)
BFSを用いた前処理+トポロジカルソートで解く．
各本を頂点とする，下記の有向グラフGを考える．
G：本iを読むために前提となる本jが存在する時，本jから本iに向かって有向辺を張ったグラフ
G上でトポロジカルソートを行うと，各本をどのような順番で読むことが可能かを求めることができる．この順序orderとする．
その上で本1を読むために必要になる本のみを，orderから，orderでの順番を保持したまま抽出すればよい．
本1を読むために必要な本の集合は，Gとは辺の向きを逆にしたグラフ上で，本1から到達可能な頂点の集合となり，BFSで求められる．
最悪計算量は，O(N+M) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<int> > adj(n),r_adj(n);
    vector<int> indeg(n,0);
    rep(i,n){
        int c;
        scanf("%d",&c);
        indeg[i]=c;
        while(c--){
            scanf("%d",&j);j--;
            adj[j].push_back(i);
            r_adj[i].push_back(j);
        }
    }
    auto bfs=[&]()->vector<bool>{
        queue<int> que;
        vector<bool> vis(n,false);
        vis[0]=true;
        que.push(0);
        while(que.size()){
            int now=que.front();que.pop();
            for(int nxt : r_adj[now])if(vis[nxt]==false){
                vis[nxt]=true;
                que.push(nxt);
            }
        }
        return vis;
    };
    auto tsort=[&]()->void{
        int i;
        vector<int> order;
        vector<bool> is_required=bfs();
        queue<int> que;
        rep(i,n)if(indeg[i]==0)que.push(i),order.push_back(i);
        while(que.size()){
            int now=que.front();que.pop();
            for(int nxt:adj[now]){
                indeg[nxt]--;
                if(indeg[nxt]==0){
                    order.push_back(nxt);
                    que.push(nxt);
                }
            }
        }
        vector<int> ans;
        rep(i,order.size())if(is_required[order[i]])ans.push_back(order[i]);
        ans.pop_back();
        rep(i,ans.size()-1)printf("%d ",ans[i]+1);printf("%d\n",ans[i]+1);
    };
    tsort();
    return 0;
}