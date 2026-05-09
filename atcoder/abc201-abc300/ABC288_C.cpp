/*アルゴリズムと工夫点(Don’t be cycle/CPU: 71 ms Memory: 15464 KB  Length: 1092 B)
※グラフ=連結であるとは限らないことに気づかず，2WAしてしまった...悔しい．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL -1
using namespace std;
typedef long long ll;

typedef pair<int,int> p;

int n,m;
vector<vector<int> > adj;
vector<int> visited;

int bfs(int s){
    int ans=0,i,j;
    queue<int> que;
    que.push(s);
    visited[s]=s;
    while(que.size()){
        for(int nxt:adj[que.front()]){
            if(nxt!=visited[que.front()]){
                if(visited[nxt]==NIL){
                    visited[nxt]=que.front();
                    que.push(nxt);
                }else{
                    ans++;
                }
            }
        }
        que.pop();
    }
    return ans/2;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    adj=vector<vector<int> >(n);
    visited=vector<int>(n,NIL);
    while(m--){
        scanf("%d%d",&i,&j);
        adj[--i].push_back(--j);
        adj[j].push_back(i);
    }
    j=0;
    rep(i,n)
        if(visited[i]==NIL)
            j+=bfs(i);
    printf("%d\n",j);
    return 0;
}