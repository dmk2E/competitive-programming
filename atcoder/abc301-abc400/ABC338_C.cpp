/*アルゴリズムと工夫点(Leftover Recipes/CPU: 72 ms  Memory: 3936 KB  Length: 932 B)
料理Aをx個作ると固定した時、料理Bをいくつ作ることができるかは、持っている材料がなくなるまで料理Bを作ればよく、その時の個数y個とすると、全体として作ることができる料理の数はx+y個になる。このyは二分探索で求める
ことができる。従って、最悪計算量は、O(MAX_Q*(n+log2(MAX_Q)))<10^8 となり高速に求めることができる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 10
#define MAX_Q 1000000
using namespace std;

int n, a[MAX_N], b[MAX_N], q[MAX_N];

bool judge(int x) {
	int i;
	rep(i, n) {
		if ((long long)q[i] < (long long)a[i] * x)
			return false;
	}
	return true;
}

int searchMax() {
	int left = 0, right = MAX_Q + 1, mid;
	while (left < right) {
		mid = (left + right) / 2;
		if (judge(mid))
			left = mid + 1;
		else
			right = mid;
	}
	return left - 1;
}

int main() {
	int i, j, max = -1, temp;
	scanf("%d",&n);
	rep(i, n)
		scanf("%d",&q[i]);
	rep(i, n)
		scanf("%d", &a[i]);
	rep(i, n)
		scanf("%d", &b[i]);
	j = 0;
	while(1) {
		if ((temp = searchMax() + j) > max)
			max = temp;
		//printf("j:%d,temp:%d\n", j, temp);
		rep(i, n) {
			q[i] -= b[i];
			if (q[i] < 0)
				break;
		}
		if (i < n)
			break;
		j++;
	}
	printf("%d\n", max);
	return 0;
}