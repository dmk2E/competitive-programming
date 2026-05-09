/*アルゴリズムと工夫点(Insertion/CPU: 1 ms  Memory: 3812 KB  Length: 557 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
using namespace std;

int n;
string s;

int main() {
	int i, d[MAX_N], j = 0, minD = MAX_N + 1;
	scanf("%d", &n);
	cin >> s;
	rep(i, s.length()) {
		if (s[i] == '(')
			j++;
		else
			j--;
		d[i] = j;
		if (minD > d[i])
			minD = d[i];
	}
	if (minD < 0)
		rep(i, -minD)
			putchar('(');
	cout << s << flush;
	if (minD < 0) {
		rep(i, d[s.length() - 1] - minD)
			putchar(')');
	}else
		rep(i, d[s.length() - 1])
			putchar(')');
	return 0;
}