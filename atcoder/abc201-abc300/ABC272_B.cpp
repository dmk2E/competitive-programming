/*アルゴリズムと工夫点(Everyone is Friends/CPU: 1 ms Memory: 3760 KB  Length: 615 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<vector<bool> > flag(n,vector<bool>(m,false));
    rep(i,m){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&j);
            flag[j-1][i]=true;
        }
    }
    rep(i,n)rep(j,i){
        rep(k,m)if(flag[i][k]&&flag[j][k])break;
        if(k==m){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}