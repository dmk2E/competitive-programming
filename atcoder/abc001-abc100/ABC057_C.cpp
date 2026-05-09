/*アルゴリズムと工夫点(Digits in Multiplication/CPU:  ms  Memory:  KB  Length:  B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

int f(long long a, long long b) {//計算量はO(log10(max(a,b)))で、最大約10回。二分探索で高速化もできるが、最大10回なので処理時間にはあまり影響しない。
	int cnt=0;
	while (a > 0 || b > 0) {
		a /= 10;
		b /= 10;
		cnt++;
	}
	return cnt;
}

long long n;

int main() {//全体の計算量はO(√n*10)≒10^6 となり十分高速。
	int i, max, min, tmp;
	scanf("%lld",&n);
	for (i = 1, max = (int)sqrt(n),min=11; i <= max; i++) {   //二つの約数の対称性より、√nまで線形探索すればよい。
		if (n % (long long)i == 0) {
			if ((tmp = f(i, n / (long long)i)) < min)
				min = tmp;
			//printf("%d %lld→%d\n", i, n / i, tmp);
		}
	}
	printf("%d\n",min);
	return 0;
}