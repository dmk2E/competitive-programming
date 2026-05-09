/*アルゴリズムと工夫点(月曜土曜素因数/CPU: 30 ms  Memory: 3732 KB  Length: 960 B)
先に月曜土曜素数を列挙しておき、その後与えられる月曜土曜数の約数を全列挙し、その約数が月曜土曜素数であるものを昇順で保持して出力する。
整数xについて、x=a*b(a<=b)を満たす2つの整数の組(a,b)を考えた時、0<=a<=√x,√x<=b<=x を満たす。従って、xの約数を全列挙するのは、0<=a<=√x の範囲の整数でxを割り、割り切れた場合に(a,b)=(a,x/a)として記録すればよい。
従って、約数の全列挙はO(√x) を満たす。
300000までの整数で、月曜土曜素数であるかを判定する配列MDPは、整数が小さい順に作成していく。まず、7*n+1,7*n+6を小さい順に見ていき、その約数を全列挙して、その約数に月曜土曜素数が含まれていないかで「true」か「false」を決定
していく。この配列作成の最悪計算量は、O(n√n)=10^(7.5)<10^8。一度作成したら、それ以降配列作成の計算量は発生しないため、個々の入力値の判定の最悪計算量は、O(√n)≒10^(2.5)となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 300000
using namespace std;

int n;
set<int> ans;
bool MDP[MAX_N + 1];

bool isMDP(int x) {
	int i, max = sqrt(x);
	for (i = 2; i <= max; i++) {
		if (x % i == 0 && (MDP[i] || MDP[x / i]))
			return false;
	}
	return true;
}

void initMDP() {
	int i, j;
	MDP[6] = true;
	for (i = 1; 7 * i + 1 <= MAX_N; i++) {
		if (isMDP(7 * i + 1))
			MDP[7 * i + 1]=true;
		if (isMDP(7 * i + 6))
			MDP[7 * i + 6]=true;
	}
}

int main() {
	int i, max;
	set<int>::iterator it;
	initMDP();
	while (1) {
		scanf("%d",&n);
		if (n == 1)
			break;
		printf("%d:",n);
		if (MDP[n])
			printf(" %d\n", n);
		else {
			max = sqrt(n);
			for (i = 2; i <= max; i++)
				if (n % i == 0) {
					if (MDP[i])
						ans.insert(i);
					if (MDP[n / i])
						ans.insert(n / i);
				}
			for (it = ans.begin(); it != ans.end(); it++) {
				printf(" %d", *it);
			}
			puts("");
		}
		ans.clear();
	}
	return 0;
}