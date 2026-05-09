/*アルゴリズムと工夫点(Ancestor/CPU: 1 ms Memory: 3844 KB  Length: 788 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<int> > adj(n);
    rep(i,n-1){
        scanf("%d",&j);
        j--;
        adj[i+1].push_back(j);
        adj[j].push_back(i+1);
    }
    queue<int> que;
    const int NIL=-1;
    vector<int> vis(n,NIL);
    que.push(0);
    vis[0]=0;
    while(que.size()){
        i=que.front();que.pop();
        rep(j,adj[i].size()){
            if(vis[adj[i][j]]==NIL){
                vis[adj[i][j]]=vis[i]+1;
                que.push(adj[i][j]);
            }
        }
    }
    printf("%d\n",vis[n-1]);
    return 0;
}