/*アルゴリズムと工夫点(Sentou/CPU: 15 ms  Memory: 3828 KB  Length: 395 B)
そのままシミュレーションで解ける。最悪計算量はO(n) となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

typedef long long ll;

int n;
ll tt,t;

int main() {
	ll ts, sum = 0, tf;
	scanf("%d%lld",&n,&tt);
	scanf("%lld",&ts);
	tf = ts + tt;
	while (--n) {
		scanf("%lld",&t);
		if (t > tf) {
			sum += tf - ts;
			ts = t;
		}
		tf = t + tt;
	}
	sum += tf - ts;
	printf("%lld\n",sum);
	return 0;
}