/*アルゴリズムと工夫点(レ/CPU: 2 ms Memory: 3916 KB  Length: 884 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100
using namespace std;

int n,m;
vector<int> adj[MAX_N];

int dfs(int par,int now,vector<int>& ans){
    int i,j=now;
    //printf("dfs(%d,%d){",par,now);
    for(i=0;i<adj[now].size();i++){
        if(par!=adj[now][i]&&now<=adj[now][i])j=dfs(now,adj[now][i],ans);
    }
    ans.push_back(now+1);
    //printf("}");
    return j;
}

int main(){
    int i,j;
    vector<int> ans;
    scanf("%d%d",&n,&m);
    rep(i,m){
        scanf("%d",&j);
        j--;
        adj[j].push_back(j+1);
        adj[j+1].push_back(j);
    }
    j=0;
    while(j<n){
        //printf("sta:%d\n",j);
        j=dfs(-1,j,ans);
        j++;
        //printf("end:%d\n",j);
    }
    rep(i,ans.size()-1)
        printf("%d ",ans[i]);
    printf("%d\n",ans[i]);
    return 0;
}