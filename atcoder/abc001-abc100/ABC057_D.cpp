/*アルゴリズムと工夫点(Maximum Average Sets/CPU: 1 ms  Memory: 3928 KB  Length: 1303 B)
n個の中からj個の品物を選んだ時の、価値の最大値は、「dp[i][j]:1～i+1番目の品物の中からj個品物を選んだ時の、価値の総和の最大値」とした動的計画法で解ける。従って、選んだ品物の価値の平均の最大値は、
max(dp[n-1][j]/j(a<=j<=b))となる。
次に、その最大値を取る品物の選び方は、dpの各値と共に、配列cntに埋めていく(cnt[i][j]:価値の総和がdp[i][j]となる時の、選び方の総数)。dp[i-1][j-1]+v!=dp[i-1][j] のとき、dp[i][j]=max(dp[i-1][j-1]+v,dp[i-1][j])となるから、
cnt[i][j]=max(cnt[i-1][j-1],dp[i-1][j])。dp[i-1][j-1]+v=dp[i-1][j] の時、dp[i][j]の値は、その二通りの方法で作られるから、cnt[i][j]=cnt[i-1][j-1]+cnt[i-1][j] となる。
最悪計算量O(n^2)<10^4 より、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 50
#define EPS (1e-10)
using namespace std;

int n, a, b;
long long dp[MAX_N][MAX_N + 1] = { 0 }, cnt[MAX_N][MAX_N + 1] = { 0 };

long double fAbs(long double a) {
	return a <EPS ? -a : a;
}

void showDP() {
	int i, j;
	puts("dp");
	rep(i, n) {
		rep(j, n+1)
			printf("%lld ", dp[i][j]);
		puts("");
	}
	puts("cnt");
	rep(i, n) {
		rep(j, n + 1)
			printf("%lld ", cnt[i][j]);
		puts("");
	}
}

int main() {
	int i, j;
	long long count = 0, v;
	long double max = -1.0, tmp;   //double型だと、誤差？で1つだけWAになる。
	scanf("%d%d%d",&n,&a,&b);
	scanf("%lld",&v);
	dp[0][1] = v;
	cnt[0][0] = cnt[0][1] = 1;
	rep(i, n-1) {
		scanf("%lld",&v);
		rep(j, n + 1) {
			dp[i + 1][j] = dp[i][j];
			cnt[i + 1][j] = cnt[i][j];
			if (j - 1 >= 0){
				if (dp[i + 1][j] < dp[i + 1][j - 1] + v) {
					dp[i + 1][j] = dp[i][j - 1] + v;
					cnt[i + 1][j] = cnt[i][j - 1];
				}
				else if(dp[i + 1][j] == dp[i][j - 1] + v){
					cnt[i + 1][j] += cnt[i][j-1];
				}
			}
		}
	}
	//showDP();
	for (j = a;j<=b;j++){
		if ((tmp = (long double)dp[i][j] / (long double)j) > max) {
			max = tmp;
			count = cnt[i][j];
		}
		else if (fAbs(tmp - max)<EPS)   //浮動小数点数型の値の等価演算は、微小な値EPSを用いて行う。
			count += cnt[i][j];
	}
	printf("%.7Lf\n%lld\n",max,count);
	return 0;
}