/*アルゴリズムと工夫点(President/CPU: 14 ms Memory: 5400 KB  Length: 774 B)
動的計画法で解く．
以下のDPテーブルを考える．
dp[i][j] := [1,i+2) 番目の選挙区の全議席を獲得するか否か決めた時，合計j議席あるための最小の鞍替え人数
ここで，ある選挙区の議席を獲得するために必要な鞍替え人数は，max(0,(その選挙区の人数の過半数) - (高橋派の人数)) である．
最悪計算量は，O(N*MAX_Z) < 10^8 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_Z (int)(1e5)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,sum_z = 0;
    const ll INF = (1e15);
    ll ans = INF;
    scanf("%d",&n);
    vector<ll> dp(MAX_Z+1,INF);
    dp[0] = 0;
    while(n--){
        int x,y,z,cost;
        scanf("%d%d%d",&x,&y,&z);
        sum_z += z;
        cost = max(0,(x+y)/2 + 1 - x);
        vector<ll> nxt = dp;
        rep(i,MAX_Z+1){
            if(dp[i] != INF)nxt[i+z] = min(nxt[i+z],dp[i] + cost);
        }
        swap(dp,nxt);
    }
    for(i = (sum_z/2)+1;i <= MAX_Z;i++)ans = min(ans,dp[i]);
    printf("%lld\n",ans);
    return 0;
}