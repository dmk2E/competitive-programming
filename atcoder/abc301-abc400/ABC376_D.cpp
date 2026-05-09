/*アルゴリズムと工夫点(Cycle/CPU: 59 ms Memory: 15212 KB  Length: 1001 B)
頂点1を起点に幅優先探索を行い，その途中で頂点1を訪れることができる場合，それが最短閉路距離となる．
最悪計算量はO(N+M)<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<vector<int> > adj(n);
    while(m--){
        scanf("%d%d",&i,&j);
        adj[i-1].push_back(j-1);
    }
    const int NIL=-1;
    vector<int> visited(n,NIL);
    auto bfs=[&](int now)->int{
        int i,j;
        queue<int> que;
        que.push(now);
        visited[now]=1;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(adj[now][i]==0){
                    return visited[now];
                }else if(visited[adj[now][i]]==NIL){
                    que.push(adj[now][i]);
                    visited[adj[now][i]]=visited[now]+1;
                }
            }
        }
        return NIL;
    };
    printf("%d\n",bfs(0));
    return 0;
}