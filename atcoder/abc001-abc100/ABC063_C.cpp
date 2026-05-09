/*アルゴリズムと工夫点(Bugged/CPU: 13 ms  Memory: 4096 KB  Length: 536 B)
i問目までで、得点しうる点数の集合dp[i]とすると、dp[i]=(dp[i-1]の全ての整数値)+Siとなる。また最大得点は10000であることから、dp[i].size<=10^4 となるから、最悪計算量はO(n*max(dp[i].size))<=10^6 となるから、
十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
using namespace std;

int n, s;

int main() {
	int i, max = 0;
	set<int> v;
	stack<int> sta;
	scanf("%d", &n);
	v.insert(0);
	rep(i, n) {
		scanf("%d", &s);
		for (int x : v) {
			if ((x + s) % 10 > 0 && x + s > max)
				max = x + s;
			sta.push(x + s);
		}
		while (sta.size()) {
			v.insert(sta.top()); sta.pop();
		}
		//printf("max:%d\n", max);
		//printf("size:%d\n", v.size());
	}
	printf("%d\n", max);
	return 0;
}