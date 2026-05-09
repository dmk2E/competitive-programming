/*アルゴリズムと工夫点(Gather the Maps!/CPU: 20 ms  Memory: 3464 KB  Length: 1348 B)
動的計画法で解く。dp[i][j]:i番目の人がj日目の時点で持っているチケットの状態(←これは2進数で表現する)
値の更新は、互いにスケジュールが空いている人同士で、前日の時点でのチケットの状態を論理和で更新すれば実現できる。最悪計算量はO(30*n^2)<10^5より、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 50
#define MAX_D 30
using namespace std;

int n, f;
long long dp[MAX_N][MAX_D + 1];
bool avai[MAX_N][MAX_D+1];

/*
void showDP1() {
	int i, j;
	rep(i, n) {
		rep(j, MAX_D)
			printf("%lld ", dp[i][j]);
		printf("%lld\n", dp[i][j]);
	}
}

void toBinary(long long x) {
	int i;
	rep(i, n) {
		if (x >> n - i - 1 & 1)
			putchar('1');
		else
			putchar('0');
	}
}

void showDP2() {
	int i, j;
	rep(i, n) {
		rep(j, MAX_D) {
			toBinary(dp[i][j]); putchar(' ');
		}
		toBinary(dp[i][j]); putchar('\n');
	}
}
*/
void init() {
	int i, j;
	rep(i,n)
		rep(j, MAX_D + 1) {
			dp[i][j] = 0;
		}
	rep(i, n)
		rep(j, MAX_D+1)
			avai[i][j] = false;
}

int searchMin() {
	int i, j, k;
	long long tmp=1;
	rep(j, MAX_D + 1) {
		rep(i, n) {
			if (j == 0) {
				dp[i][j] = tmp;
				tmp <<= 1;
			}
			else {
				dp[i][j] = dp[i][j - 1];
				rep(k, n) {
					if (i != k && avai[i][j] && avai[i][j] == avai[k][j])
						dp[i][j] |= dp[k][j-1];
				}
				if (dp[i][j] == tmp-1)
					return j;
			}
		}
	}
	return -1;
}

int main() {
	int i, j, k=0, min;
	while (1) {
		scanf("%d",&n);
		if (!n)
			break;
		min = MAX_D + 1;
		init();
		rep(i, n) {
			scanf("%d",&f);
			while (f--) {
				scanf("%d",&j);
				avai[i][j] = true;
			}
		}
		printf("%d\n",searchMin());
		//showDP2();
	}
	return 0;
}

/*
void showDP() {
	int i, j;
	rep(i, n) {
		rep(j, MAX_D)
			printf("%d ", dp[i][j]);
		printf("%d\n", dp[i][j]);
	}
}

int searchMin() {
	int i, j, k;
	rep(j, MAX_D + 1) {
		rep(i, n) {
			if (j == 0)
				dp[i][j] = 1;
			else {
				dp[i][j] = dp[i][j - 1];
				rep(k, n) {
					if (i != k && avai[i][j] && avai[i][j] == avai[k][j] && dp[i][j] < dp[i][j - 1] + dp[k][j - 1])
						dp[i][j] = dp[i][j - 1] + dp[k][j - 1];
					if (dp[i][j] == n)
						return j;
				}
			}
		}
	}
	return -1;
}
*/