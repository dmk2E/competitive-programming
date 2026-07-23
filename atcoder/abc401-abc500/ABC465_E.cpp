/*アルゴリズムと工夫点(Digit Circus/CPU: 84 ms Memory: 3948 KB  Length: 1264 B)
桁DP で解く．
下記のDPテーブルを用いた，動的計画法を考える．
 dp[i][j][k][s] := i桁目まで決定した時，
                   状態が j ∈ [0 (N 未満), 1 (N と一致)]，
                   桁和を3で割った余りがkで，
                   使った数字の集合 s ∈ [0, 2 ^ 10)
このテーブルで，3つの条件それぞれを1つだけ満たす値の個数を求めればよい．
最悪計算量は，O(log10(N) * 2 * 3 * 2 ^ (10) * 10) < 10 ^ 8 となり，間に合う．
※ (j, k, s) = (1, 0, 0) を，個数「1」を持つ初期状態とした方が，遷移が書きやすい
※ 「N以下の値」という条件は，DPの遷移で表現
*/
#include<iostream>
#include<vector>
#include<bit>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string n;

int main(){
    int i, j, k, ii;
    cin >> n;

    vector<vector<vector<int> > > dp(2, vector<vector<int> >(3, vector<int>(1 << 10, 0)));
    dp[1][0][0] = 1;
    for(char c : n){
        int cur_num = c - '0';
        vector<vector<vector<int> > > nxt(2, vector<vector<int> >(3, vector<int>(1 << 10, 0)));

        rep(j, 2)rep(k, 3)rep(ii, 1 << 10){
            rep(i, 10){
                if(j == 1 && i > cur_num)continue;
                
                int nxt_j = i < cur_num ? 0 : j;
                int nxt_k = (k + i) % 3;
                int nxt_s = (i == 0 && ii == 0) ? ii : (ii | (1 << i));

                nxt[nxt_j][nxt_k][nxt_s] = (nxt[nxt_j][nxt_k][nxt_s] + dp[j][k][ii]) % MOD;
            }
        }

        swap(dp, nxt);
    }

    int ans = -1;
    rep(j, 2)rep(k, 3)rep(ii, 1 << 10){
        int cnt = (k % 3 == 0) + ((ii >> 3) & 1) + (__builtin_popcount(ii) == 3);
        if(cnt == 1)ans = (ans + dp[j][k][ii]) % MOD;
    }

    printf("%d\n", ans);
    return 0;
}