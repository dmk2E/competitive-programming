/*アルゴリズムと工夫点(Easy Graph Problem（★2）/CPU: 31 ms Memory: 9076 KB  Length: 827 B)
わざわざDFSで解かなくても良かった...
※グラフの基本を知ろう
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<vector<int> > adj(n,vector<int>(0));
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    vector<bool> visited(n,false);
    auto dfs=[&](auto& f,int now)->int{
        int i,cnt=0,count=0;
        visited[now]=true;
        rep(i,adj[now].size()){
            if(now>adj[now][i])count++;
            if(visited[adj[now][i]]==false)
                cnt+=f(f,adj[now][i]);
        }
        return cnt+(count==1);
    };
    printf("%d\n",dfs(dfs,0));
    return 0;
}