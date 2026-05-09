/*アルゴリズムと工夫点(Reindeer and Sleigh/CPU: 103 ms  Memory: 7008 KB  Length: 590 B)
引けるソリの台数を最大化する問題。引くソリを一つ選ぶ際、同じソリ1台でも、できるだけ必要なトナカイの数は小さい方がよい。従って、必要なトナカイの数が小さい順に引くソリを選んでいけばよい。
二分探索と累積和を用いることで、計算量は、O(q*lon2(n))となり、十分高速になる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 200000
using namespace std;

typedef long long ll;

int n,q;
ll r[MAX_N],x,sum[MAX_N+1];

int main() {
	int i, left, right, mid;
	scanf("%d%d",&n,&q);
	rep(i, n)
		scanf("%lld",&r[i]);
	sort(r,r+n);
	sum[0] = 0;
	rep(i, n)
		sum[i + 1] = r[i] + sum[i];
	while (q--) {
		scanf("%lld",&x);
		left = 0;
		right = n + 1;
		while (left < right) {
			mid = (left + right) / 2;
			if (sum[mid] > x)
				right = mid;
			else
				left = mid + 1;
		}
		printf("%d\n", left - 1);
	}
	return 0;
}