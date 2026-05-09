/*アルゴリズムと工夫点(Count Connected Components/CPU: 1 ms Memory: 3892 KB  Length: 965 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
using namespace std;
typedef long long ll;

int n,m;
vector<int> adj[MAX_N];
vector<bool> visited;

void bfs(int x){
    int i;
    queue<int> que;
    que.push(x);
    visited[x]=true;
    while(que.size()){
        for(i=0;i<adj[que.front()].size();i++){
            if(visited[adj[que.front()][i]]==false){
                que.push(adj[que.front()][i]);
                visited[adj[que.front()][i]]=true;
            }
        }
        que.pop();
    }
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    visited=vector<bool>(n,false);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    j=0;
    rep(i,n)
        if(visited[i]==false){
            j++;
            bfs(i);
        }
    printf("%d\n",j);
    return 0;
}