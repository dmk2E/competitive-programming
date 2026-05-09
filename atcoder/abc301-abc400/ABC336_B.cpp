/*アルゴリズムと工夫点(CTZ/CPU: 1 ms  Memory: 3876 KB  Length: 227 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;

int main() {
	int i;
	scanf("%d", &n);
	for (i = 0; n>0&&(1 & n) == 0; i++)
		n /= 2;
	printf("%d\n", i);
	return 0;
}