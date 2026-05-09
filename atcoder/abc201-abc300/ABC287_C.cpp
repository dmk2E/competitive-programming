/*アルゴリズムと工夫点(Path Graph?/CPU: 75 ms Memory: 15228 KB  Length: 1148 B)
閉路を持たない，1本の連結グラフとなるか判定すればよい．BFSをベースとした解法の場合，最悪計算量はO(N+M)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N (int)(2e5)
#define NIL -1
using namespace std;
typedef long long ll;

int n,m;
vector<int> adj[MAX_N],visited;

bool bfs(int s){
    int cnt;
    queue<int> que;
    visited[s]=n;
    que.push(s);
    while(que.size()){
        cnt=0;
        for(int x:adj[que.front()]){
            if(x==visited[que.front()])continue;
            cnt++;
            if(cnt>=2)return false;
            if(visited[x]==NIL){
                que.push(x);
                visited[x]=que.front();
            }else
                return false;
        }
        que.pop();
    }
    return true;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    visited=vector<int>(n,NIL);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    rep(i,n)if(adj[i].size()==1)break;
    if(i==n||bfs(i)==false)
        puts("No");
    else{
        rep(i,n)if(visited[i]==NIL)break;
        printf("%s\n",i==n?"Yes":"No");
    }
    return 0;
}