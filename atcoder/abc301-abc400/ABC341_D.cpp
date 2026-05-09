/*アルゴリズムと工夫点(Only one of two/CPU: 1 ms  Memory: 3888 KB  Length: 1064 B)
n<mである時、m*y<n*x<n*(x+1)<...<m*(y+1)という関係式が必ず成立する箇所が周期的に現れる。1からある値Xまでの整数値で、NとMの内ちょうど一方のみで割り切れる数zは z=[X/N]+[X/M]-2*[X/lcm(N,M)] と表すことができる。
X=m*yの時、Xに対するzがちょうどk以上となるようなyの値を二分探索で求める。z=kとなり、m*y%n>0であれば、m*yが答えとなる。そうでなければ、m*(y-1)<n*x<m*yを満たす範囲内に、z=kとなるxの値は存在する。この範囲内で、
z=kとなるxの値を二分探索すれば解ける。従って最悪計算量はO(log2(K))となり十分高速。
※正整数a,bの最小公倍数lcm,最大公約数gcmとすると、a*b=lcm*gcmを満たすことを覚えておくこと。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

long long n, m, k;

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	long long left, mid, right, temp, lcm;
	scanf("%lld%lld%lld", &n, &m, &k);
	left = 1;
	right = 2 * k;
	lcm = n*m/gcd(n, m);
	if (n > m)
		swap(n, m);
	while (left < right) {
		mid = (left + right) / 2;
		if ((temp = m * mid / n + mid - 2 * (m * mid / lcm)) < k)
			left = mid + 1;
		else
			right = mid;
	}
	if ((m * left) % n > 0 && (temp = m * left / n + left - 2 * (m * left / lcm)) == k) {
		printf("%lld\n", m * left);
	}
	else {
		//printf("temp:%lld\n",temp);
		right = m * left / n + 1;
		left = m * (left - 1) / n;
		while (left < right) {
			//printf("left:%lld right:%lld\n", left, right);
			mid = (left + right) / 2;
			if ((temp = n * mid / m + mid - 2 * (n * mid / lcm)) < k)
				left = mid + 1;
			else
				right = mid;
		}
		printf("%lld\n", n * left);
	}
	//printf("temp:%lld\n", temp);
	return 0;
}