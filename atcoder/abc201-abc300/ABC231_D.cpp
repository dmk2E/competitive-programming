/*アルゴリズムと工夫点(Neighbors/CPU: 33 ms Memory: 8888 KB  Length: 1180 B)
人を頂点と捉え，条件をグラフに落とし込み、判定はBFSで行う．
最悪計算量はO(N+M)<10^6 となり十分高速．
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
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    vector<bool> visited(n,false);
    auto bfs=[&](int now)->int{
        //printf("now:%d\n",now);
        queue<int> que;
        int i,cnt=0;
        que.push(now);
        visited[now]=true;
        cnt++;
        while(que.size()){
            now=que.front();que.pop();
            if(adj[now].size()>2)return 0;
            rep(i,adj[now].size()){
                if(visited[adj[now][i]]==false){
                    visited[adj[now][i]]=true;
                    cnt++;
                    que.push(adj[now][i]);
                }
            }
        }
        //printf("%d\n",cnt);
        return cnt;
    };
    j=0;
    rep(i,n)if((int)adj[i].size()<=1&&visited[i]==false)j+=bfs(i);
    printf("%s\n",j==n?"Yes":"No");
    return 0;
}