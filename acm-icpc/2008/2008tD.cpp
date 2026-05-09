/*アルゴリズムと工夫点(お姫様の危機/CPU: 5270 ms  Memory: 12684 KB  Length: 2236 B)
血液の残り時間の種類分都市を増やした無向グラフにおいてダイクストラ法を用いればよい。
最悪計算量は、O((n*(m+1)+k*(m+1))*log2((n*(m+1)+k*(m+1)))≒10^7<10^8 より高速。データセットの数によっては数秒かかるが、、、、。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
#define MAX_M 100
#define WHITE 1
#define BLACK 0
#define NIL -1
using namespace std;

typedef struct data {
	int now, m, sum;

	data(int nnow = 0, int mm = 0, int ssum = 0) :now(nnow), m(mm), sum(ssum) {}

	bool operator<(const data& k) const {
		return sum < k.sum;
	}
}Data;

typedef pair<int, int> p;

int n, m, l, k, a, h;
bool cold[MAX_N];
vector<p > adj[MAX_N];

int dijk() {
	int i, j;
	bool color[MAX_N][MAX_M + 1];
	Data now;
	priority_queue<Data> PQ;
	rep(i, n)
		rep(j, m + 1)
			color[i][j] = WHITE;
	PQ.push(Data(a, m));
	while (PQ.size()) {
		do {
			now = PQ.top(); PQ.pop();
		} while (PQ.size()>0 && color[now.now][now.m] == BLACK);
		if (color[now.now][now.m] == BLACK)
			break;
		//printf("Now now:%d m:%d sum:%d\n", now.now,now.m, -now.sum);
		color[now.now][now.m] = BLACK;
		if (now.now == h)
			return -now.sum;
		rep(i, adj[now.now].size()) {
			if (now.m - adj[now.now][i].second >= 0 && color[adj[now.now][i].first][now.m - adj[now.now][i].second] == WHITE) {
				PQ.push(Data(adj[now.now][i].first, now.m - adj[now.now][i].second, now.sum - adj[now.now][i].second));
				//printf("New now:%d m:%d sum:%d\n", adj[now.now][i].first, now.m, -now.sum);
			}
		}
		if (cold[now.now]) {
			for (; now.m < m;) {
				now.m++;
				now.sum--;
				rep(i, adj[now.now].size()) {
					if (now.m - adj[now.now][i].second >= 0 && color[adj[now.now][i].first][now.m - adj[now.now][i].second] == WHITE) {
						PQ.push(Data(adj[now.now][i].first, now.m - adj[now.now][i].second, now.sum - adj[now.now][i].second));
						//printf("New now:%d m:%d sum:%d\n", adj[now.now][i].first, now.m, -now.sum);
					}
				}
			}
		}
	}
	return NIL;
}

int main() {
	int i, j, kk;
	while (1) {
		scanf("%d%d%d%d%d%d", &n, &m, &l, &k, &a, &h);
		if (!(n || m || l || k || a || h))
			break;
		rep(i, n)
			cold[i] = false;
		cold[a] = cold[h] = true;
		rep(i, l) {
			scanf("%d",&j);
			cold[j] = true;
		}
		while (k--) {
			scanf("%d%d%d",&i,&j,&kk);
			adj[i].push_back(make_pair(j, kk));
			adj[j].push_back(make_pair(i, kk));
		}
		if ((i = dijk()) == NIL)
			puts("Help!");
		else
			printf("%d\n", i);
		rep(i, n)
			adj[i].clear();
	}
	return 0;
}