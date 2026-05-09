/*アルゴリズムと工夫点(Xor Sum/CPU: 1 ms  Memory: 3852 KB  Length: 521 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_H 60
#define PATTERN 3
#define MOD 1000000007
using namespace std;

long long n,dp[MAX_H+1][PATTERN];

int main() {
	int i, j, k, ii;
	cin >> n;
	dp[MAX_H][0] = 1;
	for(i=MAX_H-1;i>=0;i--)
		rep(j,PATTERN)
			rep(k, PATTERN) {
				ii = 2*j+((n>>i)&1)-k;
				if (ii > 2)
					ii = 2;
				if (ii >= 0)
					dp[i][ii] = (dp[i][ii] + dp[i + 1][j]) % MOD;
			}
	printf("%lld\n",((dp[0][0]+dp[0][1])%MOD+dp[0][2])%MOD);
	return 0;
}