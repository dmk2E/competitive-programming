/*アルゴリズムと工夫点(Simple path/CPU: 94 ms Memory: 16688 KB  Length: 1142 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x,y;

int main(){
    int i,j,k;
    scanf("%d%d%d",&n,&x,&y);
    x--;y--;
    vector<vector<int> > adj(n);
    rep(i,n-1){
        scanf("%d%d",&j,&k);
        j--;k--;
        adj[j].push_back(k);
        adj[k].push_back(j);
    }
    const int NIL=-1;
    vector<int> par(n,NIL);
    auto bfs=[&](int x,int y)->void{
        int i;
        queue<int> que;
        par[x]=x;
        que.push(x);
        while(que.size()){
            x=que.front();que.pop();
            rep(i,adj[x].size()){
                if(par[adj[x][i]]==NIL){
                    par[adj[x][i]]=x;
                    que.push(adj[x][i]);
                }
            }
        }
    };
    bfs(x,y);
    vector<int> ans;
    ans.push_back(y);
    while(par[y]!=y)
        ans.push_back(y=par[y]);
    rep(i,ans.size()-1){
        printf("%d ",ans[(int)ans.size()-1-i]+1);
    }
    printf("%d\n",ans[(int)ans.size()-1-i]+1);
    return 0;
}