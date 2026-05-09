/*アルゴリズムと工夫点(Mixing Experiment/CPU: 167 ms  Memory: 29608 KB  Length: 1085 B)
動的計画法で解ける。最大公約数を求めるgcd関数を用いて、物質の混合比がma:mbとなるための最小予算を求めた。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 40
#define MAX_D 400
#define INF 4001
using namespace std;

int n,ma,mb,dp[MAX_N+1][MAX_D+1][MAX_D+1];

int gcd(int a,int b) {
	int tmp;
	if (a == 0 || b == 0)
		return -1;
	while (b > 0) {
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

void showDP(int k) {
	int i, j;
	rep(i, 11) {
		rep(j, 11)
			printf("%4d ", dp[k][i][j]);
		puts("");
	}
}

int main() {
	int i, j, k, a, b, c, tmp, min=INF;
	rep(i, MAX_D + 1)
		rep(j, MAX_D + 1)
			dp[0][i][j] = INF;
	dp[0][0][0] = 0;
	cin >> n >> ma >> mb;
	rep(k,n) {
		cin >> a >> b >> c;
		rep(i,MAX_D+1)
			rep(j, MAX_D + 1) {
				dp[k + 1][i][j] = dp[k][i][j];
				if (i - a >= 0 && j - b >= 0&&dp[k][i-a][j-b]+c<dp[k+1][i][j])
					dp[k+1][i][j] = dp[k][i - a][j - b] + c;
				if ((tmp = gcd(i, j)) > 1 && i / tmp == ma && j / tmp == mb && min > dp[k + 1][i][j])
					min = dp[k + 1][i][j];
			}
	}
	//showDP(n);
	if (dp[n][ma][mb] < min)
		min = dp[n][ma][mb];
	printf("%d\n",min==INF?-1:min);
	return 0;
}