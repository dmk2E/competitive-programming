/*アルゴリズムと工夫点(Counting Ls/CPU: 104 ms  Memory: 39016 KB  Length: 713 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 2000
using namespace std;

int line[MAX_N][MAX_N + 1] = {0}, row[MAX_N + 1][MAX_N] = { 0 }, n;
char s[MAX_N][MAX_N + 1];

int main() {
	int i, j;
	long long cnt = 0;
	char tmp;
	cin >> n;
	rep(i, n) {
		//scanf_s("%s",s[i],MAX_N+1);
		scanf("%s", s[i]);
	}
	rep(j, n)
		rep(i, n) {
		row[i + 1][j] = row[i][j];
		if (s[i][j] == 'o')
			row[i + 1][j]++;
	}
	rep(i,n)
		rep(j, n) {
			line[i][j + 1] = line[i][j];
			if (s[i][j] == 'o')
				line[i][j + 1]++;
		}
	rep(i, n) {
		rep(j, n) {
			if (s[i][j] == 'o') 
				cnt += (line[i][n] - 1) * (row[n][j]-1);
		}
	}
	printf("%lld\n", cnt);
	return 0;
}