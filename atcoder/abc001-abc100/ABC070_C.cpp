/*アルゴリズムと工夫点(Multiple Clocks/CPU: 300 ms  Memory: 3888 KB  Length: 345 B)
入力される全てのtの最小公倍数を求めればよい。最悪計算量は, O(N*log2(max(T)))<10^4 となり、十分高速。
*/
#include <iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;
long long last,now;

long long gcd(long long a,long long b){
	return b==0?a:gcd(b,a%b);
}

int main() {
	scanf("%d%lld",&n,&last);
	while(--n){
		scanf("%lld",&now);
		last=last/gcd(last,now)*now;
	}
	printf("%lld\n",last);
	return 0;
}