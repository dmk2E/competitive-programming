/*アルゴリズムと工夫点(T-shirts/CPU: 1 ms  Memory: 3880 KB  Length: 810 B)
買ったロゴ入りTシャツの数に対して、条件を満たす行動ができるかはO(n)で分かる。従って、買うロゴ入りTシャツの数を2分探索し、最小のTシャツ購入数を求めた。計算量はO(n*log2(n))<10^4 で十分高速。
※二分探索しなくても、nの最大値1000より、購入する数が0の場合から順に調べていき、O(n^2)で求めても間に合う。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 1000
using namespace std;

int n, m, s[MAX_N];

bool judge(int logo) {
	int i, mn = m, ln = logo;
	rep(i, n) {
		switch (s[i]) {
		case 0:
			mn = m;
			ln = logo;
			break;
		case 1:
			if (mn > 0)
				mn--;
			else if (ln > 0)
				ln--;
			else
				return false;
			break;
		default:
			if (ln > 0)
				ln--;
			else
				return false;
			break;
		}
		//printf("%d %d\n",mn,ln);
	}
	return true;
}

int main() {
	int left, right, mid, i;
	scanf("%d%d", &n, &m);
	rep(i, n)
		scanf("%1d", &s[i]);
	left = 0; right = n + 1;
	while (left < right) {
		mid = (left + right) / 2;
		if (judge(mid))
			right = mid;
		else
			left = mid + 1;
	}
	printf("%d\n", left);
	return 0;
}