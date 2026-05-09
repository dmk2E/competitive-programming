/*アルゴリズムと工夫点(Tile Pattern/CPU: 433 ms  Memory: 11864 KB  Length: 1473 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 1000
using namespace std;

int n, q, a, b, c, d, p[MAX_N][MAX_N], sum[MAX_N + 1][MAX_N + 1] = { 0 };

void showSum() {
	int i, j;
	rep(i, n + 1) {
		rep(j, n + 1)
			printf("%d ", sum[i][j]);
		puts("");
	}
}

long long s(int sy,int sx,int ey,int ex) {
	return (long long)sum[ey+1][ex+1]-sum[ey+1][sx]-sum[sy][ex+1]+sum[sy][sx];
}

long long g(int gy,int gx) {
	int y,x;
	long long cnt, sum = 0;
	if (gy < 0 || gx < 0)
		return 0;
	cnt = ((long long)(gy + 1) / n) * ((gx + 1) / n);
	sum += cnt * s(0, 0, n-1, n-1);
	cnt = (gx + 1) / n;
	if(gy%n<n-1)
		sum += cnt * s(0, 0, gy%n, n-1);
	cnt = (gy + 1) / n;
	if(gx%n<n-1)
		sum += cnt * s(0, 0,n-1,gx%n);
	if(gy%n<n-1&&gx%n<n-1)
		sum += s(0, 0, gy % n, gx % n);
	return sum;
}

long long f(int a, int b, int c, int d) {
	//printf("g(%d,%d):%lld g(%d,%d):%lld g(%d,%d)=%lld g(%d,%d)=%lld\n",c,d,g(c,d),c,b-1,g(c,b-1),a-1,d,g(a-1,d),a-1,b-1,g(a-1,b-1));
	return g(c, d) - g(a-1, d) - g(c, b-1) + g(a-1, b-1);
}

int main() {
	int i, j;
	long long tmp, temp, base;
	scanf("%d%d", &n, &q);
	rep(i, n) {
		getchar();
		rep(j, n) {
			if (getchar() == 'B')
				p[i][j] = 1;
			else
				p[i][j] = 0;
		}
	}
	rep(i, n)
		rep(j, n)
			sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + p[i][j];
	while (q--) {
		cin >> a >> b >> c >> d;
		printf("%lld\n",f(a,b,c,d));
	}
	return 0;
}