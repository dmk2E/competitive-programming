/*アルゴリズムと工夫点(ポロック予想/CPU: 250 ms  Memory: 13304 KB  Length: 1345 B)
solved[i]:整数iを正四面体数の和として表すために必要な正四面体数の個数の最小値 solvedOdd[i]:整数iを奇数の正四面体数の和として表すために必要な奇数の正四面体数の個数の最小値 とし、あらかじめ配列solvedと
配列solveOddを作成しておき、入力値xに対して、solved[x]とsolvedOdd[x]の値を出力する。
solvedの作成方法:1～1000000(=MAX_N)までの整数値xを頂点とし、それぞれの頂点xから y=x+polk[i] を満たす整数値yの頂点へ辺を伸ばした有向重み無しグラフにおいて幅優先探索(bfs)を行い、最小個数を求め、作成する。
solveOddの作成方法:polk[i]が奇数であるもののみ使う以外、配列solvedの作成方法と同じ。
solved,solvedOddそれぞれの作成方法の最悪計算量は、O(MAX_N*(配列polkの要素数))≒10^6*10^2=10^8 となるが、ポロック予想では最小個数は最大でも5個となるため、実際の計算量はもっと小さくなると考えられる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1000000
#define MAX_P 200
#define NIL 0
using namespace std;

int n, solved[MAX_N + 1] = { 0 }, solvedOdd[MAX_N + 1] = { 0 }, polk[MAX_P], p = 0;//polk[i]=(i+1)*(i+2)*(i+3)/6

void bfs() {
	int i, cnt = p, now;
	queue<int> que;
	rep(i, p) {
		que.push(polk[i]);
		solved[polk[i]] = 1;
	}
	while (que.size()) {
		now = que.front(); que.pop();
		rep(i, p) {
			if (now + polk[i] > MAX_N)
				break;
			if (solved[now + polk[i]] == NIL) {
				cnt++;
				que.push(now + polk[i]);
				solved[now + polk[i]] = solved[now] + 1;
			}
		}
		if (cnt == MAX_N)
			break;
	}
}

void bfsOdd() {
	int i, cnt = 0, now;
	queue<int> que;
	rep(i, p) {
		if (polk[i] % 2 == 1) {
			cnt++;
			que.push(polk[i]);
			solvedOdd[polk[i]] = 1;
		}
	}
	while (que.size()) {
		now = que.front(); que.pop();
		rep(i, p) {
			if (polk[i] % 2 == 1) {
				if (now + polk[i] > MAX_N)
					break;
				if (solvedOdd[now + polk[i]] == NIL) {
					cnt++;
					que.push(now + polk[i]);
					solvedOdd[now + polk[i]] = solvedOdd[now] + 1;
				}
			}
		}
		if (cnt == MAX_N)
			break;
	}
}

int main() {
	int i, j;
	i = 1;
	while ((j = i * (i + 1) * (i + 2) / 6) <= MAX_N) {
		polk[p++] = j;
		i++;
	}
	bfs();
	bfsOdd();
	while (1) {
		scanf("%d", &n);
		if (!n)
			break;
		printf("%d %d\n", solved[n], solvedOdd[n]);
	}
	return 0;
}