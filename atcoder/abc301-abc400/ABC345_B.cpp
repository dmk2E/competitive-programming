/*アルゴリズムと工夫点(Integer Division Returns/CPU: 1 ms  Memory: 3884 KB  Length: 240 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

long long x;

int main() {
	scanf("%lld",&x);
	if(x%10==0)
		printf("%lld\n",x/10);
	else
		printf("%lld\n",x>=0?x/10+1:x/10);
	return 0;
}