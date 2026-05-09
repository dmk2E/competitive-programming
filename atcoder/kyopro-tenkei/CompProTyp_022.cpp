/*アルゴリズムと工夫点(Cubic Cake/CPU: 1 ms  Memory: 3900 KB  Length: 336 B)
「全てのピースを立方体にする必要がある」->「全てのA,B,Cが等しい値になるように切断できるか」であり、できるだけそれぞれの値が大きい方が切断できる回数は少なくなる。したがって、その値に切断することができる値の中で最大の
値を求めればよい。その値は、A,B,Cの最大公約数となる。よって、最悪計算量は、O(log2(max(A,B,C))) となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

long long a,b,c;

long long gcd(long long a,long long b){
	return b==0?a:gcd(b,a%b);
}

int main() {
	int i;
	long long gcm;
	scanf("%lld%lld%lld",&a,&b,&c);
	gcm=gcd(a,gcd(b,c));
	printf("%lld\n",a/gcm+b/gcm+c/gcm-3);
	return 0;
}