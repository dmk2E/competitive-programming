/*アルゴリズムと工夫点(迷図と命ず/CPU: 0 ms  Memory: 3420 KB  Length: 2056 B)
与えられるデータの意味に注意して幅優先探索で解ける。
最悪計算量はO(h*w*4)=O(h*w)≒10^3 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 30
#define MAX_W 30
#define MAX_D 4
#define NIL 0
using namespace std;

typedef struct data {
	int y, x;

	data(int yy = 0, int xx = 0) :y(yy), x(xx) {}
}Data;

int w, h, visited[MAX_H][MAX_W], dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };   //visited[i][j]:迷路上で、(i,j)の位置の最短距離を格納する。最短距離が求められてない位置に関しては「0」を格納しておくことで、訪問済みのマーカーの役割を果たす。
bool mapW[MAX_H][MAX_W - 1] = {0}, mapH[MAX_H - 1][MAX_W] = {0};   //mapW[i][j]:(i,j)の右側に壁が存在するかどうか mapH[i][j]:(i,j)の下に壁が存在するかどうか

int bfs() {
	int i, j;
	Data now;
	queue<Data> que;
	rep(i, h)
		rep(j, w)
			visited[i][j] = NIL;
	que.push(Data(0, 0));
	visited[0][0] = 1;
	while (que.size()) {
		now = que.front(); que.pop();
		if (now.y == h - 1 && now.x == w - 1)
			return visited[now.y][now.x];
		rep(i, MAX_D) {
			if (now.y + dy[i] < h && now.y + dy[i] >= 0 && now.x + dx[i] < w && now.x + dx[i] >= 0 &&visited[now.y + dy[i]][now.x + dx[i]] == NIL) {
				switch (i) {
					case 0:
						if (mapH[now.y + dy[i]][now.x + dx[i]] == false) {
							que.push(Data(now.y + dy[i], now.x + dx[i]));
							visited[now.y + dy[i]][now.x + dx[i]] = visited[now.y][now.x] + 1;
						}
						break;
					case 1:
						if (mapW[now.y][now.x] == false) {
							que.push(Data(now.y + dy[i], now.x + dx[i]));
							visited[now.y + dy[i]][now.x + dx[i]] = visited[now.y][now.x] + 1;
						}
						break;
					case 2:
						if (mapH[now.y][now.x] == false) {
							que.push(Data(now.y + dy[i], now.x + dx[i]));
							visited[now.y + dy[i]][now.x + dx[i]] = visited[now.y][now.x] + 1;
						}
						break;
					default :
						if (mapW[now.y + dy[i]][now.x + dx[i]] == false) {
							que.push(Data(now.y + dy[i], now.x + dx[i]));
							visited[now.y + dy[i]][now.x + dx[i]] = visited[now.y][now.x] + 1;
						}
						break;
				}
			}
		}
	}
	return NIL;
}

int main() {
	int i, j, k;
	while (1) {
		scanf("%d%d", &w, &h);
		if (!(w || h))
			break;
		rep(i, 2 * h - 1) {
			if (i % 2 == 0) {
				rep(j, w - 1) {
					scanf("%d", &k);
					mapW[i / 2][j] = (k == 1);
				}
			}
			else {
				rep(j, w) {
					scanf("%d", &k);
					mapH[i / 2][j] = (k == 1);
				}
			}
		}
		printf("%d\n", bfs());
	}
	return 0;
}