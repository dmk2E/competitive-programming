/*アルゴリズムと工夫点(Find Permutation/CPU: 78 ms Memory: 15772 KB  Length: 1127 B)
トポロジカルソートのアルゴリズムを使うとは.....
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

int n,m,indeg[MAX_N]={0};
vector<int> adj[MAX_N];

bool tsort(vector<int>& ans){
    int i,cnt=1;
    queue<int> que;
    bool color[MAX_N]={0};
    rep(i,n)if(indeg[i]==0){que.push(i);color[i]=true;}
    while(que.size()){
        if(que.size()>1)return false;
        ans[que.front()]=cnt++;
        rep(i,adj[que.front()].size()){
            indeg[adj[que.front()][i]]--;
            if(indeg[adj[que.front()][i]]==0){
                que.push(adj[que.front()][i]);
                color[adj[que.front()][i]]=true;
            }
        }
        que.pop();
    }
    return cnt-1==n;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<int> ans(n);
    while(m--){
        scanf("%d%d",&i,&j);
        adj[i-1].push_back(j-1);
        indeg[j-1]++;
    }
    if(tsort(ans)){
        puts("Yes");
        rep(i,n-1)
            printf("%d ",ans[i]);
        printf("%d\n",ans[i]);
    }else
        puts("No");
    return 0;
}