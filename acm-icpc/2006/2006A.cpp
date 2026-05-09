/*アルゴリズムと工夫点(Dirichlet's Theorem on Arithmetic Progressions/CPU: 0 ms  Memory: 4084 KB  Length: 604 B)
エラトステネスの篩で10^6までの値の素数判定を行える配列isPrimeを作成する。その後、与えられる等差数列の値を一つずつ見ていき、素数になった回数を変数cntに保持しておき、cnt==nとなった時の値を出力する。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_PRIME 1000000
using namespace std;

int a, d, n;
bool isPrime[MAX_PRIME+1];

void erato() {
	int i, j;
	rep(i, MAX_PRIME + 1)
		isPrime[i] = true;
	isPrime[0] = isPrime[1] = false;
	rep(i, MAX_PRIME + 1) {
		if (isPrime[i]) {
			j = i*2;
			while (j < MAX_PRIME + 1) {
				isPrime[j] = false;
				j += i;
			}
		}
	}
}

int main() {
	int cnt = 0;
	erato();
	while (1){
		cin >> a >> d >> n;
		if (!(a || d || n))
			break;
		cnt = 0;
		while (cnt<n) {
			if (isPrime[a])
				cnt++;
			a += d;
		}
		printf("%d\n",a-d);
	}
	return 0;
}