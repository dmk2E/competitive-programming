/*アルゴリズムと工夫点(ICPC 得点集計ソフトウェア/CPU: 0 ms  Memory: 3452 KB  Length: 420 B)
線形的に各点を加算していく作業のついでに最大点数と最小点数を求め、条件を満たす平均値を求めるようにする。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define  MAX_S 1000
using namespace std;

int n, s;

int main() {
	int i, sum, max, min;
	while (1) {
		scanf("%d",&n);
		if (!n)
			break;
		sum = 0; max = -1; min = MAX_S + 1;
		rep(i, n) {
			scanf("%d",&s);
			sum += s;
			if (max < s)
				max = s;
			if (min > s)
				min = s;
		}
		sum -= max + min;
		sum /= (n - 2);
		printf("%d\n", sum);
	}
	return 0;
}