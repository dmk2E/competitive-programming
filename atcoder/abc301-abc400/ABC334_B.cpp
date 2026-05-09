/*アルゴリズムと工夫点(Christmas Trees/CPU: 1 ms  Memory: 3880 KB  Length: 804 B)
数直線の問題は、基準点を原点に持ってくることで簡単化できる場合が多い。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

long long a, m, l, r;

long long num(long long x) {   //地点x以下の範囲で、最も東のクリスマスツリーの座標がkmである時、kを返す関数。
	if (x > 0)
		return x / m;
	else {
		x = -x;
		return x % m == 0 ? -x / m : -(x / m + 1);
	}
}

int main() {
	scanf("%lld%lld%lld%lld",&a,&m,&l,&r);
	l -= a;
	r -= a;
	printf("%lld\n", num(r) - num(l - 1));
	return 0;
}

/*初見時のコード:アルゴリズムと工夫点(Christmas Trees/CPU: 1 ms  Memory: 3880 KB  Length: 804 B)
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

long long a, m,l, r;

int main() {
	long long cnt = 0,tmp;
	scanf("%lld%lld%lld%lld",&a,&m,&l,&r);
	if (l <= a && a <= r) {
		cnt = 1;
		tmp = r;
		tmp -= a;
		cnt += tmp / m;
		tmp = a;
		tmp -= l;
		cnt += tmp / m;
	}
	else {
		//printf("l:%lld r:%lld a:%lld\n",l,r,a);
		if (r < a) {
			tmp = a;
			tmp -= l;
			cnt += tmp / m;
			tmp = a;
			tmp -= r;
			cnt -= tmp / m;
			//printf("tmp:%llu\n",tmp);
			if (tmp % m == 0)
				cnt++;
			//printf("tmp:%llu\n", tmp);
		}
		else {
			tmp = r;
			tmp -= a;
			cnt += tmp / m;
			tmp = l;
			tmp -= a;
			cnt -= tmp / m;
			if (tmp % m == 0)
				cnt++;
			//printf("tmp:%llu\n", tmp);
		}
	}
	printf("%lld\n",cnt);
	return 0;
}
*/