/*アルゴリズムと工夫点(Number of Shortest paths/CPU: 84 ms Memory: 16256 KB  Length: 1051 B)
幅優先探索を元に，別で保持した各頂点への最短距離から各頂点に最短で到達するパス数を数え上げる．最悪計算量はO(N+M)<10^6 となり，十分高速．
※初見ACできた!でも，あまりの所で「%」と打ったはずが「&」となっていたせいで1WAしてしまった．悔しい．
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
#define MOD ((int)(1e9)+7)
#define NIL -1
using namespace std;

int n,m;
vector<int> adj[MAX_N];

int bfs(){
    int i,j,color[MAX_N],path[MAX_N]={0};
    queue<int> que;
    rep(i,n)
        color[i]=NIL;
    color[0]=0;
    path[0]=1;
    que.push(0);
    while(que.size()){
        j=que.front();que.pop();
        rep(i,adj[j].size()){
            if(color[adj[j][i]]==NIL){
                color[adj[j][i]]=color[j]+1;
                path[adj[j][i]]=path[j];
                que.push(adj[j][i]);
            }else if(color[adj[j][i]]==color[j]+1){
                path[adj[j][i]]=(int)(((long long)path[adj[j][i]]+path[j])%MOD);
            }
        }
    }
    return path[n-1];
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    printf("%d\n",bfs());
    return 0;
}