/*アルゴリズムと工夫点(Sum of Consecutive Integers/CPU: 0 ms  Memory: 3308 KB  Length: 588 B)
正の整数a～b(0<a<b)の総和Sを求める公式を用いて、和がnとなるような連続する2つ以上の正の整数の組み合わせを全探索して解を求める。まず先端のaの値の範囲は1～n-1 のn-1通りであり、aの値を固定するとbの値に対してSの
値は単調性を持つから、aに対するS=nとなるbの値は a<b<n の範囲で二分探索することにより求めることができる。従って最悪計算量はO(n*log2(n))≒10^4となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;

int sumA2B(int a,int b) {//a～bまでの総和を返す。
	return b * (b + 1) / 2 - a * (a - 1) / 2;
}

int main() {
	int i, left, right, mid, cnt;
	while (1) {
		scanf("%d", &n);
		if (!n)
			break;
		cnt = 0;
		rep(i, n - 1) {
			left = i + 2;
			right = n;
			while (left < right) {
				mid = (left + right) / 2;
				if (sumA2B(i + 1, mid) == n)
					break;
				else if (sumA2B(i + 1, mid) < n)
					left = mid + 1;
				else
					right = mid;
			}
			if (left < right)
				cnt++;
		}
		printf("%d\n", cnt);
	}
	return 0;
}