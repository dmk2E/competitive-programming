/*アルゴリズムと工夫点(Widespread/CPU: 19 ms  Memory: 4204 KB  Length: 849 B)
敵全員分の総HPを0にしないと、全ての魔物を消し去ることはできない->1回の爆発でできるだけ敵の総HPを削りたい->その時に最もHPが高い敵を中心に爆発させればよい。つまり、貪欲法で解ける。
しかし貪欲法だとシミュレーション的解法となり、計算量が膨大となってしまう。そこで、Tには単調性があることを利用した二分探索で解く。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 100000
#define MAX_B 1000000000
using namespace std;

int n, a, b, h[MAX_H];

bool judge(long long t) {
	int i;
	long long cnt = 0;
	rep(i, n) {
		if (h[i] - (long long)b * t > 0) {
			//printf("%lld\n", ((long long)h[i] - (long long)b * t) / (a - b));
			cnt += (h[i] - (long long)b * t) / (a - b);
			if ((h[i] - (long long)b * t) % (a - b) > 0)
				cnt++;
		}
	}
	return cnt <= t;
}

int main() {
	int i, left = 1, right = MAX_B + 1, mid;
	scanf("%d%d%d", &n, &a, &b);
	rep(i, n)
		scanf("%d", &h[i]);
	while (left < right) {
		mid = (left + right) / 2;
		//printf("mid:%d\n", mid);
		if (judge(mid))
			right = mid;
		else
			left = mid + 1;
		//printf("left:%d right:%d\n", left, right);
	}
	printf("%d\n", left);
	return 0;
}