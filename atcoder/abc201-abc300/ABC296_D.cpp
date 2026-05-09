/*アルゴリズムと工夫点(M<=ab/CPU: 5 ms  Memory: 3900 KB  Length: 403 B)
aを固定して考えたとき、b=(M/aの切り上げ)となりbの値が一意に定まる。ここで、「a<=b」という大小関係を付加しても一般性を失わないという、整数問題でおなじみの手法を用いると、
a<=b=(M/aの切り上げ)<M/a+1 となり式変形を行って、a^2-a-M<0 よって、a≒√M となる。したがって、このようなaの値すべてに対する解を求めればよい。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

long long n,m;

int main() {
	int a,max;
	long long b,min;
	scanf("%lld%lld",&n,&m);
	max=(int)sqrt(m)+1;
	for(a=1,min=LLONG_MAX;a<=max;a++){
		if(a>n)
			break;
		if(m%a==0)
			b=m/a;
		else
			b=m/a+1;
		if(b<=n&&a*b<min)
			min=a*b;
	}
	printf("%lld\n",min==LLONG_MAX?-1:min);
	return 0;
}