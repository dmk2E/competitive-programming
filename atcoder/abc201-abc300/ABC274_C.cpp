/*アルゴリズムと工夫点(Ameba/CPU: 75 ms Memory: 27524 KB  Length: 1095 B)
各アメーバを頂点とみなしてBFSをするだけ．
最悪計算量はO(3*(2*N+1))=O(N)≒10^6 より十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<int> > adj(2*n+2,vector<int>(0));
    rep(i,n){
        scanf("%d",&j);
        adj[j].push_back(2*(i+1));
        adj[j].push_back(2*(i+1)+1);
        adj[2*(i+1)].push_back(j);
        adj[2*(i+1)+1].push_back(j);
        //printf("%d<->%d,%d\n",j,2*(i+1),2*(i+1)+1);
    }
    const int NIL=-1;
    vector<int> visited(2*n+2,NIL);
    auto bfs=[&]()->void{
        queue<int> que;
        int i,now;
        que.push(1);
        visited[1]=0;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(visited[adj[now][i]]==NIL){
                    visited[adj[now][i]]=visited[now]+1;
                    que.push(adj[now][i]);
                }
            }
        }
    };
    bfs();
    rep(i,2*n+1)printf("%d\n",visited[i+1]);
    return 0;
}