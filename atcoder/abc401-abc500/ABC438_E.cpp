/*アルゴリズムと工夫点(Heavy Buckets/CPU: 327 ms Memory: 77996 KB  Length: 980 B)
ダブリングを利用したDPで解く．
まず，通常のダブリングで配列aを求める．
a[i][j] := 人j から 2^(i)回 バケツを移動させた時，そのバケツを持っている人
その後，ダブリングの要領で，下記のDPを解く．
dp[i][j] := 人j から 2^(i)回 バケツを移動させた時の水量
遷移は，dp[i + 1][j] = dp[i][a[i][j]] + dp[i][j] で O(1)となる．
このdpテーブルを用いることで，T回目の操作の直後にバケツBに入っている水の量を高速に求める．
最悪計算量は，O( (N + Q) * log2(max(Ti)) ) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, q;

int main(){
    int i, j;
    const int MAX = 30;
    scanf("%d%d", &n, &q);
    vector<vector<int> > a(MAX + 1, vector<int>(n));
    rep(i, n){
        scanf("%d", &a[0][i]);
        a[0][i]--;
    }
    vector<vector<ll> > dp(MAX + 1, vector<ll>(n));
    rep(j, n)dp[0][j] = j + 1;
    rep(i, MAX)rep(j, n){
        a[i + 1][j] = a[i][a[i][j]];
        dp[i + 1][j] = dp[i][a[i][j]] + dp[i][j];
    }
    while(q--){
        int t, b, now;
        scanf("%d%d", &t, &b);
        now = b - 1;
        ll ans = 0;
        i = 0;
        while(t > 0){
            if(t & 1){
                ans += dp[i][now];
                now = a[i][now];
            }
            t >>= 1;
            i++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}