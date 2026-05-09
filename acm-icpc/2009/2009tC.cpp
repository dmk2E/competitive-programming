/*アルゴリズムと工夫点(Brave Princess Revisited/CPU: 0 ms  Memory: 3840 KB  Length: 1423 B)
宿を頂点とみなし、頂点に着いた時の予算として取りうる値の場合だけ頂点の数を増やした拡張ダイクストラ方で解ける。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
#define MAX_L 100
using namespace std;

typedef struct inn {
	int to, d, e;

	inn(int tto, int dd, int ee) :to(tto), d(dd), e(ee) {}
}Inn;

typedef struct data {
	int now, cost, l;

	data(int nnow=0, int ccost = 0, int ll = 0) :now(nnow),cost(ccost), l(ll) {}

	bool operator< (const data& k) const {
		return cost < k.cost;
	}
}Data;

int n, m, l;
vector<Inn> adj[MAX_N];

int dijk() {
	int i;
	Data now;
	bool color[MAX_N][MAX_L + 1] = { 0 };
	priority_queue<Data> PQ;
	PQ.push(Data(0, 0, l));
	while (PQ.size()) {
		do {
			now = PQ.top(); PQ.pop();
		} while (color[now.now][now.l] && PQ.size() > 0);
		//printf("Now:(%d,%d,%d)\n", now.now, -now.cost, now.l);
		if (color[now.now][now.l])
			break;
		if (now.now == n - 1)
			return -now.cost;
		color[now.now][now.l] = true;
		for (Inn d : adj[now.now]) {
			if (color[d.to][now.l] == false)
				PQ.push(Data(d.to, now.cost - d.e, now.l));
			if (now.l - d.d >= 0 && color[d.to][now.l - d.d] == false)
				PQ.push(Data(d.to, now.cost, now.l - d.d));
		}
	}
	return -1;
}

int main() {
	int i, j, k, ll;
	while (1) {
		scanf("%d%d%d", &n, &m, &l);
		if (!(n || m || l))
			break;
		while (m--) {
			scanf("%d%d%d%d", &i, &j, &k, &ll);
			adj[--i].push_back(Inn(--j, k, ll));
			adj[j].push_back(Inn(i, k, ll));
		}
		printf("%d\n",dijk());
		rep(i, n)
			adj[i].clear();
	}
	return 0;
}