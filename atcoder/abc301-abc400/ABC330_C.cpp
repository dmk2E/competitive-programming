/*アルゴリズムと工夫点(Minimize Abs 2/CPU: 67 ms  Memory: 3812 KB  Length: 1040 B)
絶対値の値になっているから、x,yの取りうる値は0～√Dとなる。従って、√Dを超える整数値max_xをまず二分探索で求める。計算量はO(log2(D))。
その後、0～max_xの範囲でxの値を固定し、|x^2+y^2-D|の値が正の範囲で最小となるようなyの値y_maxを二分探索で求める。xの値を固定した時、y=y_maxの時、またはy=y_max-1の時に|x^2+y^2-D|の値は最小となる。これを利用して
、求める最小値を決定する。計算量はO(√Dlog2(√D))≒10^7となり、高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_MIN 10000000
#define MAX_D 2000000000000
using namespace std;

long long d;

int main() {
	int min, i, left, right, mid, j;
	long long tmp, ans = MAX_D + 1, temp;
	cin >> d;
	left = 0;
	right = MAX_MIN;
	while (left < right) {
		mid = (left + right) / 2;
		if ((long long)mid * mid < (long long)d)
			left = mid + 1;
		else
			right = mid;
	}
	min = left;
	rep(i, min + 1) {
		tmp = (long long)i * i - d;
		left = 0; right = min + 1;
		while (left < right) {
			mid = (left + right) / 2;
			if (tmp + (long long)mid * mid < 0)
				left = mid + 1;
			else
				right = mid;
		}
		temp = tmp + (long long)left * left;
		left--;
		if (temp > abs(tmp + (long long)left * left))
			temp = abs(tmp + (long long)left * left);
		if (ans > temp)
			ans = temp;
	}
	printf("%lld\n", ans);
	return 0;
}