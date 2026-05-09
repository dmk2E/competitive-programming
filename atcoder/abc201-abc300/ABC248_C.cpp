/*アルゴリズムと工夫点(Dice Sum/CPU: 5 ms Memory: 3908 KB  Length: 597 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m,k;

int main(){
    int i,j,ii;
    scanf("%d%d%d",&n,&m,&k);
    vector<int> dp(k+1,0);
    dp[0]=1;
    rep(i,n){
        vector<int> now(k+1,0);
        rep(j,k+1)if(dp[j]>0)rep(ii,m){
            if(j+ii+1<=k)now[j+ii+1]=(now[j+ii+1]+dp[j])%MOD;
        }
        swap(dp,now);
    }
    ii=0;
    rep(i,k+1)ii=(ii+dp[i])%MOD;
    printf("%d\n",ii);
    return 0;
}