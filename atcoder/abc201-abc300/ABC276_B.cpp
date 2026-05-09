/*アルゴリズムと工夫点(Adjacency List/CPU: 62 ms Memory: 9064 KB  Length: 722 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<vector<int> > adj(n,vector<int>(0));
    while(m--){
        scanf("%d%d",&i,&j);
        adj[i-1].push_back(j-1);
        adj[j-1].push_back(i-1);
    }
    rep(i,n){
        printf("%d%c",(int)adj[i].size(),(int)adj[i].size()?' ':'\n');
        if((int)adj[i].size()>0){
            sort(adj[i].begin(),adj[i].end());
            rep(j,adj[i].size()-1)printf("%d ",adj[i][j]+1);
            printf("%d\n",adj[i][j]+1);
        }
    }
    return 0;
}