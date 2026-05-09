/*アルゴリズムと工夫点(Count Simple Paths/CPU: 109 ms Memory: 23992 KB  Length: 866 B)
DFSの動きの中で，各頂点に到達した回数がそのままパスの本数になる．
ただし，TLEしないように解が10^6を超えた時点で探索を打ち切るように対策しておくこと．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N (int)(2e5)
#define MAX (int)(1e6)
using namespace std;
typedef long long ll;

int n,m,cnt=1;
vector<int> adj[MAX_N];
vector<bool> visited;

void dfs(int now){
    int i;
    rep(i,adj[now].size()){
        if(visited[adj[now][i]]==false){
            visited[adj[now][i]]=true;
            cnt++;
            if(cnt==MAX)return ;
            dfs(adj[now][i]);
            if(cnt==MAX)return ;
            visited[adj[now][i]]=false;
        }
    }
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
    visited=vector<bool>(n,false);
    visited[0]=true;
    dfs(0);
    printf("%d\n",cnt);
    return 0;
}