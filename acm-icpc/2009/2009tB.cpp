/*アルゴリズムと工夫点(Matsuzaki Number/CPU: 860 ms  Memory: 5400 KB  Length: 1202 B)
エラトステネスの篩のアルゴリズムで、あらかじめ使う可能性がある10^6以下の素数を全列挙しておき、それを元にm(n,p)を計算する。pの最大値は100であるから、nより大きい素数を小さい順に500個ほど取り出し、その中で2数の
和を全列挙して、p番目の値をm(n,p)とした。「500」という値は目安である。素数の全列挙は最初の1回だけ行えばよいため、その処理を除いた最悪計算量は、O(log2(MAX_PRIME)+RANGE^2*log2(RANGE^2)+p)=O(RANGE^2)となる。今回
はRANGE=500としたが、計算量的にはRANGE=10^3としても、O(RANGE^2)=10^6 となるため、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_PRIME 1000000
#define RANGE 500
using namespace std;

int n, p;
vector<int> prime;

void createPrime() {   //列挙する素数の個数は10^5個未満となる。
	int i, j;
	bool isPrime[MAX_PRIME + 1];
	rep(i, MAX_PRIME + 1)
		isPrime[i] = true;
	isPrime[0] = isPrime[1] = false;
	for (i = 2; i < MAX_PRIME + 1; i++) {
		if (isPrime[i]) {
			for (j = i + i; j < MAX_PRIME + 1; j += i)
				isPrime[j] = false;
		}
	}
	rep(i, MAX_PRIME + 1)
		if (isPrime[i])
			prime.push_back(i);
}

int searchPrime(int nn) {   //整数値nnより大きい値の中の最小値を格納しているprime上の添え字を二分探索
	int left = 0, mid, right = prime.size();
	while (left < right) {
		mid = (left + right) / 2;
		if (prime[mid] > nn)
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}

int m(int n,int p) {   //pの値が最大100だから、searchPrime(n)～searchPrime(n)+500までの2つの素数の和を全列挙してp番目を返すようにすればerrorはないと仮定する。
	int i, j, max;
	priority_queue<int> PQ;
	n = searchPrime(n);
	max = n + RANGE > prime.size() ? prime.size() : n + RANGE;
	for (i = n; i < max; i++)
		for (j = i + 1; j < max; j++)
			PQ.push(-(prime[i] + prime[j]));
	for (i = n; i < max; i++)
		PQ.push(-prime[i] * 2);
	rep(i, p - 1)
		PQ.pop();
	return -PQ.top();
}

int main() {
	int i;
	createPrime();
	while (1) {
		scanf("%d%d", &n, &p);
		if (n == -1 && p == -1)
			break;
		printf("%d\n", m(n, p));
	}
	return 0;
}