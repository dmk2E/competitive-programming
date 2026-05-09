/*アルゴリズムと工夫点(離散的速度/CPU:  ms  Memory:  KB  Length:  B)
「崖登り」や「ちょろちょろロボット」同様、グラフを拡張するダイクストラ法で解くことができる。今回は都市である頂点を、到達した時の速度とどの頂点から到達したかの全パターン数分だけ増やし、ダイクストラ法を行えば
よい。最悪計算量は、O((n*MAX_V*n+m)*log2(n*MAX_V*n+m))<10^6 となり十分高速。ただし、実装の際は以下のルールに注意。
<i>目的地を出る時、また出発地に着く直前の速度は「1」に限られる。<ii>Uターン禁止(直前に訪問した都市に戻るのは禁止)
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 30
#define MAX_V 30
#define NIL -1
using namespace std;

typedef struct city {
	int id, d, c;

	city(int iid = 0, int dd = 0, int cc = 0) :id(iid),d(dd), c(cc) {}

}City;

typedef struct data {
	int now, from, v;
	double t;

	data(int nnow=0, int ffrom=0, int vv=0, double tt=0.0):now(nnow),from(ffrom),v(vv),t(tt) {}

	bool operator<(const data& k) const {
		return t < k.t;
	}
}Data;

int n, m, s, g;
vector<City> adj[MAX_N];

double dijk(int s,int g) {
	int i, j, k;
	Data now;
	priority_queue<Data> PQ;
	bool color[MAX_N][MAX_V + 1][MAX_N];   //color[i][j][k]:都市iに速さj+1で都市kからきたことを表す頂点
	rep(i, n)
		rep(j, MAX_V + 1)
			rep(k, n)
				color[i][j][k] = true;
	for (City c : adj[s])
		PQ.push(Data(c.id, s, 1, -(double)c.d));
	while (PQ.size()) {
		do {
			now = PQ.top(); PQ.pop();
		} while (PQ.size() > 0 && color[now.now][now.v][now.from] == false);
		if (color[now.now][now.v][now.from] == false)
			break;
		color[now.now][now.v][now.from] = false;
		if (now.now == g && now.v == 1)
			return -now.t;
		for (City c : adj[now.now]) {
			if (c.id == now.from)
				continue;
			if (now.v + 1 <= c.c && color[c.id][now.v + 1][now.now])
				PQ.push(Data(c.id, now.now, now.v + 1, now.t - (double)c.d / (now.v + 1)));
			if (now.v <= c.c && color[c.id][now.v][now.now])
				PQ.push(Data(c.id, now.now, now.v, now.t - (double)c.d / now.v));
			if (now.v - 1 > 0 && now.v - 1 <= c.c && color[c.id][now.v - 1][now.now])
				PQ.push(Data(c.id, now.now, now.v - 1, now.t - (double)c.d / (now.v - 1)));
		}
	}
	return NIL;
}

int main() {
	int i, j, k, ii;
	double ans;
	while (1) {
		scanf("%d%d", &n, &m);
		if (!(n || m))
			break;
		scanf("%d%d", &s, &g);
		while (m--) {
			scanf("%d%d%d%d", &i, &j, &k, &ii);
			adj[i - 1].push_back(City(j - 1, k, ii));
			adj[j - 1].push_back(City(i - 1, k, ii));
		}
		if ((ans = dijk(s - 1, g - 1)) == NIL)
			puts("unreachable");
		else
			printf("%.4f\n", ans);
		rep(i, n)
			adj[i].clear();
	}
	return 0;
}