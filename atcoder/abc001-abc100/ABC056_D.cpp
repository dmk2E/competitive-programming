/*アルゴリズムと工夫点(No Need/CPU: 281 ms  Memory: 28360 KB  Length: 1245 B)
問題文を言い変えると、総和がk以上となる全て部分集合において、消しても総和がk未満にならない要素の数を答えればよい。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 5000
#define MAX_K 5000
using namespace std;

int n,nn, k, a[MAX_N];
bool dp[MAX_N][MAX_K + 1];

void showDP() {
	int i, j;
	rep(i, n - 1) {
		rep(j, k + 1)
			printf("%d ",dp[i][j]?1:0);
		puts("");
	}
}

bool judge(int id) {
	int i = 0, j, now;
	rep(i, nn)
		rep(j, k + 1)
			dp[i][j] = false;
	i = 0;
	rep(now, nn) {
		if (now == id)
			continue;
		if (i == 0) 
			dp[i][a[now]] = true;
		else if(a[now]<k) {
			dp[i][a[now]] = true;
			rep(j, k + 1) {
				if (dp[i - 1][j]) {
					dp[i][j] = dp[i - 1][j];
					if (j + a[now] < k) {
						dp[i][j + a[now]] = true;
						if (k - a[id] <= j + a[now] && j + a[now] < k)
							return true;
					}
				}
			}
		}
		i++;
	}
	return false;
}

int main() {
	int i, left, right, mid;
	scanf("%d%d",&n,&k);
	nn = 0;
	rep(i, n) {   //そもそも値がk以上の値は絶対に必要な要素だからスルーする。
		scanf("%d", &a[nn]);
		if (a[nn] < k)
			nn++;
	}
	sort(a,a+nn);
	left = 0;
	right = nn;
	while (left < right) {
		mid = (left + right) / 2;
		//printf("%d\n",a[mid]);
		if (judge(mid))
			right = mid;
		else
			left = mid + 1;
		//showDP();
		//printf("left:%d,right:%d\n",left,right);
	}
	printf("%d\n",left);
	return 0;
}