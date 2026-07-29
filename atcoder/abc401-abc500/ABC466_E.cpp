/*アルゴリズムと工夫点(Range Flip/CPU: 113 ms Memory: 3752 KB  Length: 575 B)
動的計画法で解く．
操作する区間は交わらないため，2 * K + 1 個の区間分け（偶数番目：表，奇数番目：裏）を行う問題と捉えることが出来る．
そこで，下記のDPテーブルを満たす動的計画法で解く．
dp[i][j] := i番目のカードがj番目の区間であった時の総和の最大値
最悪計算量は，O(N * K) < 10 ^ 7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, k;

int main(){
    int i, j;

    scanf("%d%d", &n, &k);
    const int MAX_BLOCK = 2 * k + 1;
    vector<ll> dp(MAX_BLOCK, 0);
    rep(i, n){
        int a, b;
        cin >> a >> b;

        rep(j, MAX_BLOCK)dp[j] += j % 2 == 0 ? a : b;
        rep(j, MAX_BLOCK - 1)dp[j + 1] = max(dp[j + 1], dp[j]);
    }

    printf("%lld\n", dp[MAX_BLOCK - 1]);
    return 0;
}