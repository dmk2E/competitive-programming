/*アルゴリズムと工夫点(Amida, the City of Miracle/CPU: 0 ms  Memory: 3780 KB  Length: 561 B)
amida[i][j]:高さiのj番目の線が、何番目の線と繋がっているかを格納する。
上記で定義したamidaを利用して、現在のあみだくじ上の高さnowが、その最大の高さから0になるまで、それぞれの高さで横線があれば繋がっている縦線に移るという動作を繰り返すシミュレーションで解く。
計算量はO(max(あみだくじの高さ))=10^3 となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 100
#define MAX_H 1000
using namespace std;

int n, m, a, amida[MAX_H + 1][MAX_N + 1];

int main() {
	int i, j, k, now=0;
	while (1) {
		scanf("%d%d%d",&n,&m,&a);
		if (!(n || m || a))
			break;
		rep(i, MAX_H + 1)
			rep(j, n + 1)
				amida[i][j] = 0;
		while (m--) {
			scanf("%d%d%d",&i,&j,&k);
			amida[i][j] = k;
			amida[i][k] = j;
			if (now < i)
				now = i;
		}
		while (now > 0) {
			if (amida[now][a] > 0)
				a = amida[now][a];
			now--;
		}
		printf("%d\n",a);
	}
	return 0;
}