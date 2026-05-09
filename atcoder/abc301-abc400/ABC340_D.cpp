/*アルゴリズムと工夫点(Super Takahashi Bros./CPU: 115 ms  Memory: 18588 KB  Length: 1052 B)
辺の張り方に注意すれば、単純なダイクストラ法で解ける。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200000
using namespace std;

typedef pair<long long, long long> p;//(ステージ名、かかる時間)

int n, a, b, x;
vector<p> adj[MAX_N];

long long dijk() {
	bool stage[MAX_N] = { 0 };
	priority_queue<p> PQ;//(かかった時間,ステージ名)
	p now;
	PQ.push(make_pair(0, 0));
	while (PQ.size() > 0) {
		do {
			now = PQ.top(); PQ.pop();
		} while (stage[now.second] && PQ.size() > 0);
		printf("%lld %lld\n", -now.first, now.second);
		if (now.second == n - 1)
			return -now.first;
		if (stage[now.second])
			break;
		stage[now.second] = true;
		for (p temp : adj[now.second]) {
			if (stage[temp.first] == false) {
				PQ.push(make_pair(now.first - temp.second, temp.first));
			}
		}
	}
	return -1;
}

int main() {
	int i, j;
	scanf("%d", &n);
	rep(i, n) {
		scanf("%d%d%d", &a, &b, &x);
		adj[i].push_back(make_pair(i + 1, a));
		adj[i].push_back(make_pair(x - 1, b));
	}
	printf("%lld\n",dijk());
	return 0;
}