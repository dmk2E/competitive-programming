/*アルゴリズムと工夫点(お姫様のギャンブル/CPU: 0 ms  Memory: 3452 KB  Length: 387 B)
割るタイミングだけ気を付ければ、整数型の小数点以下切り捨てを利用してO(n)で解ける。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define TICKET 100
using namespace std;

int n, m, p;

int main() {
	int i, sum, x, j;
	while (1) {
		scanf("%d%d%d", &n, &m, &p);
		if (!(n || m || p))
			break;
		sum = 0;
		rep(i, n) {
			scanf("%d", &j);
			sum += j;
			if (i == m - 1)
				x = j;
		}
		printf("%d\n", x == 0 ? 0 : sum * (100 - p) / x);
	}
	return 0;
}