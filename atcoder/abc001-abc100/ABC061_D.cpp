/*アルゴリズムと工夫点(Score Attack/CPU: 1 ms  Memory: 3916 KB  Length: 978 B)
重みの最大値を求める経路問題では、重みを反転させ、最短経路問題に帰着させる(知っているアルゴリズムが使用できるように問題の値を変形する)。今回は負の重みを持つ辺が存在するから、ベルマンフォード法で求める。
ベルマンフォード法では、|V|-1回のループで単一始点最短経路を求めることができる。負閉路が存在し、かつその負閉路から頂点Nに到達できるかは、|V|回目のループで頂点Nまでの最短経路が更新されるかで判断できる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1000
#define MAX_M 2000
#define INF (1e13)
using namespace std;

typedef struct edge {
	int from, to, cost;
}Edge;

int n, m;
Edge e[MAX_M];
long long d[MAX_N];

int main() {
	int i, j;
	bool update;
	scanf("%d%d", &n, &m);
	rep(i, m) {
		scanf("%d%d%d", &e[i].from, &e[i].to, &e[i].cost);
		e[i].cost = -e[i].cost;
		e[i].from--;
		e[i].to--;
	}
	rep(i, n)
		d[i] = INF;
	d[0] = 0;
	rep(i, n - 1) {
		update = false;
		rep(j, m)
			if (d[e[j].from] != INF && d[e[j].to] > d[e[j].from] + e[j].cost) {
				d[e[j].to] = d[e[j].from] + e[j].cost;
				update = true;
			}
		if (update)
			break;
	}
	update = false;
	rep(j, m) {
		if (d[e[j].to] > d[e[j].from] + e[j].cost) {
			d[e[j].to] = d[e[j].from] + e[j].cost;
			if (e[j].to == n - 1) update = true;
		}
	}
	if (update)
		cout << "inf" << endl;
	else
		printf("%lld\n", -d[n - 1]);
	return 0;
}

/*dfsで色々やったやつ。AC*18 TLE*6(←ギリギリ) WA*6
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1000
#define NIL -1
using namespace std;

typedef struct pair<int, int> p;

int n, m;
bool able0[MAX_N] = { 0 }, ableN[MAX_N] = { 0 }, color[MAX_N] = { 0 };   //未訪問:false 訪問済み:true
vector<p> adj[MAX_N],aadj[MAX_N];

bool dfs(int now,int goal,int cnt,vector<int>& v) {
	if (now == goal && cnt > 1)
		return true;
	v.push_back(now);
	for (p x:adj[now]) {
		if (cnt + 1 <= n && dfs(x.first, goal, cnt + 1, v))
			return true;
	}
	v.pop_back();
	return false;
}

void ddfs(int now, bool able[MAX_N], vector<p> adj[MAX_N]) {
	able[now] = true;
	for (p x : adj[now]) {
		if (able[x.first] == false)
			ddfs(x.first, able, adj);
	}
}

bool isLoop() {
	int i;
	vector<int> v;
	ddfs(0, able0, adj);
	ddfs(n - 1, ableN, aadj);
	rep(i, n) {
		v.clear();
		if (able0[i] && dfs(i, i, 0, v))
			for (int j : v)
				if (ableN[j]) 
					return true;
	}
	return false;
}

long long dddfs(int now, long long sum) {
	if (now == n - 1) {
		return sum;
	}
	long long max = NIL, tmp;
	color[now] = true;
	for (p x : adj[now]) {
		if (color[x.first] == false) {
			if ((tmp = dddfs(x.first, x.second + sum)) > max||max==NIL)
				max = tmp;
		}
	}
	color[now] = false;
	return max;
}

int main() {
	int i, j, k;
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d%d", &i, &j, &k);
		adj[i - 1].push_back(make_pair(j - 1, k));
		aadj[j - 1].push_back(make_pair(i - 1, k));
	}
	if (isLoop())
		cout << "inf" << endl;
	else
		printf("%lld\n", dddfs(0, 0));
	return 0;
}
*/