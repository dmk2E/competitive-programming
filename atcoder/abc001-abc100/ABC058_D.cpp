/*アルゴリズムと工夫点(井井井/CPU: 19 ms  Memory: 3892 KB  Length: 470 B)
解を式にできるなら、式にして、その式の形から計算量を削減した解法を見つけるパターンも存在する。
今回求めるsumXやsumYは和であるから、余りを取れるのは和の項のそれぞれについてであり、項それぞれの計算途中では取れないことに注意。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MOD 1000000007
using namespace std;

typedef long long ll;

int n, m;

int main() {
	int i, j;
	long long sumX = 0, sumY = 0, tmp;
	scanf("%d%d",&n,&m);
	rep(i, n) {
		scanf("%lld",&tmp);
		sumX = (sumX+i * tmp - (n - i - 1) * tmp) % MOD;
	}
	rep(i, m) {
		scanf("%lld", &tmp);
		sumY = (sumY+i * tmp - (m - i - 1) * tmp) % MOD;
	}
	printf("%lld\n", (sumX*sumY)%MOD);
	return 0;
}
/*余りを取れるだけとったver
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MOD 1000000007
using namespace std;

typedef long long ll;

int n, m;

int main() {
	int i, j;
	long long sumX = 0, sumY = 0, tmp;
	scanf("%d%d",&n,&m);
	rep(i, n) {
		scanf("%lld",&tmp);
		sumX = (sumX+(MOD+(i * tmp)%MOD - ((n - i - 1) * tmp)%MOD)%MOD) % MOD;
	}
	rep(i, m) {
		scanf("%lld", &tmp);
		sumY = (sumY+(MOD+(i * tmp)%MOD - ((m - i - 1) * tmp)%MOD)%MOD) % MOD;
	}
	printf("%lld\n", sumX*sumY%MOD);
	return 0;
}
*/