/*アルゴリズムと工夫点(Differential Pulse Code Modulation/CPU: 570 ms  Memory: 43524 KB  Length: 982 B)
dp[i][j]:yi=jの時の最小の二乗和 とする動的計画法で解ける。最悪計算量はO(n*MAX_Y*m)<10^8 となり高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 20000
#define MAX_M 16
#define MAX_Y 255
#define INF (1e18)
using namespace std;

int n, m, c[MAX_M];
long long dp[MAX_N + 1][MAX_Y + 1];

void showDP() {
	int i, j;
	rep(i, n + 1) {
		rep(j, MAX_Y+1)
			printf("%lld ", dp[i][j]);
		puts("");
	}
}

int main() {
	int i, j, k, l, x;
	while (1) {
		scanf("%d%d", &n, &m);
		if (!(n || m))
			break;
		rep(i, m)
			scanf("%d", &c[i]);
		rep(i, n + 1)
			rep(j, MAX_Y + 1)
				dp[i][j] = INF;
		dp[0][128] = 0;
		rep(i, n) {
			scanf("%d", &x);
			rep(j, MAX_Y + 1) {
				if (dp[i][j] < INF) {
					rep(k, m) {
						l = 0 <= j + c[k] && j + c[k] <= MAX_Y ? j + c[k] : j + c[k] < 0 ? 0 : MAX_Y;
						if (dp[i + 1][l] > dp[i][j] + (l - x) * (l - x))
							dp[i + 1][l] = dp[i][j] + (l - x) * (l - x);
					}
				}
			}
		}
		//showDP();
		k = 0;
		rep(j, MAX_Y + 1) {
			if (dp[n][k] > dp[n][j])
				k = j;
		}
		printf("%lld\n", dp[n][k]);
	}
	return 0;
}