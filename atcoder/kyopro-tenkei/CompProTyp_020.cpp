/*アルゴリズムと工夫点(Log Inequality/CPU: 1 ms  Memory: 3880 KB  Length: 409 B)
logの値をそのまま計算してしまうと、浮動小数点が絡む計算となってしまい、二つの値の差の絶対値が限りなく小さい場合、大小関係を上手く判定することができなくなってしまう。そこで、式変形してlog2(a)<log2(c^b) とすると、
真数の大小関係に注目して、a<c^b かどうかの整数型の計算で大小関係を判定できる。繰り返し二乗法により、最悪計算量は O(log2(b))<10^2 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

unsigned long long a;
int b,c;

unsigned long long power(unsigned long long x,int a){
	if(a==0)
		return 1;
	unsigned long long res=power(x*x,a/2);
	if(a%2==1)
		res*=x;
	return res;
}

int main() {
	scanf("%lld%d%d",&a,&b,&c);
	printf("%s\n",a<power((unsigned long long)c,b)?"Yes":"No");
	return 0;
}