/*アルゴリズムと工夫点(Sequence/CPU: 13 ms  Memory: 4272 KB  Length: 954 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 100000
using namespace std;

int n, a[MAX_N];

int main() {
	int i, j;
	long long sum = 0, cnt = 0, min;
	bool prev;
	cin >> n;
	rep(i, n)
		scanf("%d", &a[i]);
	for (j = -1, min = 10000000000000000; j < 2; j += 2) {
		cnt = 0;
		if (j * a[0] < 0) {
			sum = j;
			cnt += a[0] - j < 0 ? -(a[0] - j) : a[0] - j;
		}
		else if (a[0] == 0) {
			sum = j;
			cnt++;
		}
		else
			sum = a[0];
		prev = sum > 0;
		rep(i, n - 1) {
			sum += a[i + 1];
			if (sum > 0) {
				if (prev) {
					cnt += sum + 1;
					sum = -1;
				}
			}
			else if (sum < 0) {
				if (!prev) {
					cnt += -sum + 1;
					sum = 1;
				}
			}
			else {
				sum = prev ? -1 : 1;
				cnt++;
			}
			prev = !prev;
			//printf("sum:%lld cnt:%lld prev:%d\n", sum, cnt, prev ? 1 : 0);
		}
		if (min > cnt)
			min = cnt;
	}
	cnt = min;
	printf("%lld\n", cnt);
	return 0;
}