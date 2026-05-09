/*アルゴリズムと工夫点(Comparison/CPU: 1 ms  Memory: 3664 KB  Length: 496 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

string a, b;

int main() {
	int i;
	cin >> a >> b;
	if (a.length() > b.length())
		puts("GREATER");
	else if(a.length()<b.length())
		puts("LESS");
	else {
		rep(i, a.length()) {
			if ((int)a[i] - (int)b[i] > 0) {
				puts("GREATER");
				break;
			}
			else if ((int)a[i] - (int)b[i] < 0) {
				puts("LESS");
				break;
			}
		}
		if (i == a.length())
			puts("EQUAL");
	}
	return 0;
}