/*アルゴリズムと工夫点(Tail of Snake/CPU: 66 ms Memory: 19956 KB  Length: 813 B)
DP で解く．
蛇の部位を，頭(i = 0) -> 胴(i = 1) -> 尾(i = 2) の順に決めていくとする．
この時，下記のような動的計画法を考える．
dp[i][j] := j個目のブロックを蛇の部位iとした時の，らしさの最大値
遷移は，dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + value_j), dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + value_j) となり，O(1) となる．
従って最悪計算量は，O(N) < 10^7 となり十分高速．
※ in-place DP で実装することで，メモリ計算量を抑えた
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    const int ROW = 3, NIL = -1;
    scanf("%d", &n);
    vector<vector<int> > abc(n, vector<int>(3));
    rep(i,n)scanf("%d", &abc[i][0]);
    rep(i,n)scanf("%d", &abc[i][1]);
    rep(i,n)scanf("%d", &abc[i][2]);
    vector<ll> dp(ROW, NIL);
    dp[0] = abc[0][0];
    for(j = 1;j < n;j++){
        vector<ll> nxt(ROW, NIL);
        rep(i, ROW)if(dp[i] != NIL){
            nxt[i] = max(nxt[i], dp[i] + abc[j][i]);
            if(i + 1 < ROW)nxt[i + 1] = max(nxt[i + 1], dp[i] + abc[j][i + 1]);
        }
        swap(dp, nxt);
    }
    printf("%lld\n", dp[2]);
    return 0;
}