/*アルゴリズムと工夫点(Choose Integers/CPU: 1 ms  Memory: 3900 KB  Length: 390 B)
a*k=b*q+c より、a*k-b*q=cという二元一次不定方程式の解が存在するかを判定すればよい。aとbが互いに素なら確実に解を持つ。互いに素でない場合、
gcd(a,b)*(aa*k-bb*q)=cという形に変形できるから、cがgcd(a,b)の倍数なら解を持つ。理由は、aaとbbは互いに素であるため、aa*k-bb*q=1の解は必ず存在するから、aa*k-bb*q=c/gcd(a,b) の解も必ず一つは存在する
から。最悪計算量はO(log2(max(a,b)))となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

int a, b, c;

int gcd(int a,int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	int tmp;
	scanf("%d%d%d",&a,&b,&c);
	tmp = gcd(gcd(a, b), c);
	a /= tmp; b /= tmp; c /= tmp;
	if ((tmp = gcd(a, b)) == 1 || c % tmp == 0)
		puts("YES");
	else
		puts("NO");
	return 0;
}