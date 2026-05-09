/*アルゴリズムと工夫点(Mr. Rito Post Office/CPU: 240 ms  Memory: 4640 KB  Length: 1782 B)
現在の町、船が停泊している町、集配番号の三つ組とするノードを用いた拡張ダイクストラ法で解けるが、最悪計算量がO((N*N*R+M)log2(N*N*R+M))≒4*10^8 となり、最大データセットで実行に数十分程かかってしまう。
→ワーシャルフロイド法で陸路、海路のみを用いる場合の最短経路をあらかじめ求めておき、DPで解く。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200
#define MAX_R 1000
#define INF (1e8)
using namespace std;

int n, m, r, z[MAX_R], adjL[MAX_N][MAX_N], adjS[MAX_N][MAX_N];

int main() {
	int i, j, k;
	int dp[MAX_R][MAX_N];
	char sl[2];
	while (1) {
		scanf("%d%d", &n, &m);
		if (!(n || m))
			break;
		rep(i,n)
			rep(j, n) {
				if(i==j)
					adjL[i][j] = adjS[i][j] = 0;
				else
					adjL[i][j] = adjS[i][j] = INF;
			}
		while (m--) {
			scanf("%d%d%d%s", &i, &j, &k, sl);
			if (sl[0] == 'L') {
				if (k < adjL[i - 1][j - 1])
					adjL[i - 1][j - 1] = k;
				if (k < adjL[j - 1][i - 1])
					adjL[j - 1][i - 1] = k;
			}
			else{
				if (k < adjS[i - 1][j - 1])
					adjS[i - 1][j - 1] = k;
				if (k < adjS[j - 1][i - 1])
					adjS[j - 1][i - 1] = k;
			}
		}
		scanf("%d", &r);
		rep(i, r) {
			scanf("%d", &z[i]);
			z[i]--;
		}
		rep(i, n) {
			rep(j, n) {
				rep(k, n) {
					if (adjL[j][k] > adjL[j][i] + adjL[i][k])
						adjL[j][k] = adjL[j][i] + adjL[i][k];
					if (adjS[j][k] > adjS[j][i] + adjS[i][k])
						adjS[j][k] = adjS[j][i] + adjS[i][k];
				}
			}
		}
		/*
		rep(i, n) {
			printf("%d:", i);
			rep(j, n)
				printf("%d(L:%d S:%d),", j, adjL[i][j], adjS[i][j]);
			puts("");
		}
		*/
		rep(i, r)
			rep(j, n)
				dp[i][j] = INF;
		rep(i, r) {
			rep(j, n) {
				if (i == 0)
					dp[i][j] = 0;
				else
					dp[i][j] = min(dp[i][j], dp[i - 1][j] + adjL[z[i - 1]][z[i]]);
				rep(k, n) {
					if (i == 0)
						dp[i][k] = adjS[z[i]][k];
					else
						dp[i][k] = min(dp[i][k], dp[i - 1][j] + adjL[z[i - 1]][j] + adjS[j][k] + adjL[k][z[i]]);
					//printf("dp[%d][%d]=%d\n", i, k, dp[i][k]);
				}
			}
		}
		i = 0;
		rep(j, n)
			if (dp[r - 1][j] < dp[r - 1][i])
				i = j;
		printf("%d\n", dp[r - 1][i]);
	}
	return 0;
}
/*拡張ダイクストラ法
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200
#define MAX_R 1000
using namespace std;

typedef struct town {//海路ならsl==trueとなる。
	int y, t;
	bool sl;

	town(int yy = 0, int tt = 0, bool ssl = true) :y(yy), t(tt), sl(ssl) {}
}Town;

typedef struct data {
	int now, sum, ship, completed;

	data(int nnow = 0, int ssum = 0, int sship = 0, int ccompleted = 0) :now(nnow), sum(ssum), ship(sship), completed(ccompleted) {}

	bool operator< (const data& k)const {
		return sum < k.sum;
	}
}Data;

int n, m, r, z[MAX_R];
vector<Town> adj[MAX_N];

int dijk() {
	int j;
	bool color[MAX_N][MAX_N][MAX_R] = { 0 };
	Data now;
	priority_queue<Data> PQ;
	PQ.push(Data(z[0], 0, z[0], 0));
	while (PQ.size()) {
		do {
			now = PQ.top(); PQ.pop();
		} while (color[now.now][now.ship][now.completed] && PQ.size());
		if (color[now.now][now.ship][now.completed])
			break;
		color[now.now][now.ship][now.completed] = true;
		//printf("(%d,%d,%d,%d)\n", now.now, -now.sum, now.ship, now.completed);
		if (z[now.completed] == now.now)
			now.completed++;
		if (now.completed == r)
			return -now.sum;
		for (Town x : adj[now.now]) {
			if (x.sl) {
				if (now.now == now.ship && color[x.y][x.y][now.completed] == false) {
					PQ.push(Data(x.y, now.sum - x.t, x.y, now.completed));
					//printf("New!(%d,%d,%d,%d)\n", x.y, -now.sum + x.t, x.y, now.completed);
				}
			}
			else if (color[x.y][now.ship][now.completed] == false) {
				PQ.push(Data(x.y, now.sum - x.t, now.ship, now.completed));
				//printf("New!(%d,%d,%d,%d)\n", x.y, -now.sum + x.t, now.ship, now.completed);
			}
		}
	}
	return -1;
}

int main() {
	int i, j, k;
	char sl[2];
	while (1) {
		scanf("%d%d", &n, &m);
		if (!(n || m))
			break;
		while (m--) {
			scanf("%d%d%d%s", &i, &j, &k, sl);
			adj[i - 1].push_back(Town(j - 1, k, sl[0] == 'S'));
			adj[j - 1].push_back(Town(i - 1, k, sl[0] == 'S'));
		}
		scanf("%d", &r);
		rep(i, r) {
			scanf("%d", &z[i]);
			z[i]--;
		}
		printf("%d\n",dijk());
		rep(i, n)
			adj[i].clear();
	}
	return 0;
}
*/