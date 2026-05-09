/*アルゴリズムと工夫点(King Bombee/CPU: 199 ms Memory: 4244 KB  Length: 961 B)
dp[i][j][k]=Aiまで決めた時に，頂点jにいて，2で割った余りがkである時の条件を満たす数列の総数．
最悪計算量は O(K*(N+M))<10^7 より高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m,k,s,t,x;

int main(){
    int i,j,ii;
    scanf("%d%d%d%d%d%d",&n,&m,&k,&s,&t,&x);
    vector<vector<int> > adj(n);
    s--;t--;x--;
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    vector<vector<int> > dp(n,vector<int>(2,0));
    dp[s][0]=1;
    while(k--){
        vector<vector<int> > now(n,vector<int>(2,0));
        rep(i,n){
            rep(j,2){
                rep(ii,adj[i].size()){
                    now[adj[i][ii]][(j+(x==adj[i][ii]))%2]+=dp[i][j];
                    now[adj[i][ii]][(j+(x==adj[i][ii]))%2]%=MOD;
                }
            }
        }
        swap(dp,now);
    }
    printf("%d\n",dp[t][0]);
    return 0;
}