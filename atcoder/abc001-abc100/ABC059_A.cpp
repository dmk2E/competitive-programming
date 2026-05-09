/*アルゴリズムと工夫点(Three-letter acronym/CPU: 1 ms  Memory: 3668 KB  Length: 462 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_ALFA 26
using namespace std;

char alfa[MAX_ALFA + 1] = "abcdefghijklmnopqrstuvwxyz";
char aalfa[MAX_ALFA + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int search(char c) {
	int i;
	rep(i, MAX_ALFA)
		if (alfa[i] == c)
			return i;
	return -1;
}

int main() {
	int i;
	string s;
	rep(i, 3) {
		cin >> s;
		cout << aalfa[search(s[0])] << flush;
	}
	cout << endl;
	return 0;
}