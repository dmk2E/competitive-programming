/*アルゴリズムと工夫点(3N Numbers/CPU: 55 ms  Memory: 6116 KB  Length: 1003 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
#define MIN -((1e14)+1)
using namespace std;

int n, a[3 * MAX_N];
long long mmax[MAX_N + 1];

int main() {
	int i, j,maxI;
	priority_queue<int> PQMax, PQMin;
	long long sumMax = 0, sumMin = 0;
	scanf("%d", &n);
	rep(i, 3 * n) {
		scanf("%d", &a[i]);
		if (i < n) {
			PQMax.push(-a[i]);
			sumMax += a[i];
		}
		else if (2 * n <= i) {
			PQMin.push(a[i]);
			sumMin += a[i];
		}
	}
	for (i = n; i <= 2 * n; i++) {
		//printf("sumMax:%lld\n", sumMax);
		mmax[i - n] = sumMax;
		sumMax += a[i];
		PQMax.push(-a[i]);
		j = PQMax.top(); PQMax.pop();
		//printf("pop:%d\n", j);
		sumMax += j;
	}
	for (i = 2 * n, maxI = n; i >= n; i--) {
		//printf("sumMin:%lld\n", sumMin);
		if ((mmax[i - n] -= sumMin) > mmax[maxI])
			maxI = i - n;
		PQMin.push(a[i - 1]);
		sumMin += a[i - 1];
		j = PQMin.top(); PQMin.pop();
		sumMin -= j;
	}
	printf("%lld\n", mmax[maxI]);
	return 0;
}