/*アルゴリズムと工夫点(Triangle (Easier)/CPU: 2 ms Memory: 3824 KB  Length: 542 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k,ans=0;
    scanf("%d%d",&n,&m);
    vector<vector<bool> > adj(n,vector<bool>(n,false));
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i][j]=adj[j][i]=true;
    }
    rep(i,n)rep(j,i)rep(k,j){
        ans+=adj[k][j]&&adj[j][i]&&adj[i][k];
    }
    printf("%d\n",ans);
    return 0;
}