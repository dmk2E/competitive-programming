/*アルゴリズムと工夫点(Cleaning Robot/CPU: 520 ms  Memory: 3416 KB  Length: 4618 B)
最初は始点との距離が最小となる点から順に幅優先探索していけばよいと考えたが、この順番では必ずしも汚れを全て消し終わるまでの総距離が最小となるとは限らない。かといって単純なdfsやbfsによる全探索だと、生成される
状態の数が多くなり、計算量の見積もりが困難&メモリが足りなかったたり、スタックオーバーフローになる可能性がある。
従って、与えられたマップにおける、汚れと開始位置を頂点とする重み付き無向完全グラフを作成し、そのグラフ上でdfsを行い、最短距離を求めることとする。頂点間の重み、つまり最短距離はマップ上でbfsを行って求める。
例として、頂点1,頂点2,頂点3の2点を結ぶ辺の総数を求める。まず頂点1を固定した時の2つ目の点の選び方を考えると、頂点2,3の2通りである。次に頂点2を固定して同様に考えるが、この時重複の分を除くため、頂点1を2つ目の
頂点に選ぶ候補の中から削除する。そうすると1通りしかなく、辺の総数は3つとなる。これを利用して、bfsを行う度、次回のbfsで用いるマップ上から今回のbfsの始点を削除するようにすることで、重複なく、隣接行列adjの各値
を求めることができる。
ここで始点を頂点番号0とし、汚れの頂点番号は1から順番に定めていくこととした。この時、マップ上の座標をキーとし、頂点番号を保持するmapで処理した。
bfsによる隣接行列adjの値決定には、最悪計算量O(h*w)*O(h*w*4)<10^6となり、作ったグラフ上でのdfsによる最短距離の全探索の最悪計算量は、グラフの頂点の数の2倍程度だから、O(h*w*2)<10^3となり、全体として十分高速と
なる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define swap(a,b,t){t=a,a=b,b=c}
#define MAX_H 20
#define MAX_W 20
#define MAX_A 400
#define NIL -1
using namespace std;

typedef pair<int, int> p;

typedef enum color {
	BLACK = -2,
	WHITE
}Color;

int w, h, adj[MAX_A][MAX_A];
char board[MAX_H][MAX_W], tmp[MAX_H][MAX_W];   //bfs時に使うマップ情報をtmp,次回のbfs時に使うマップ情報をboardに保持しておく。
map<p, int> t;   //(座標,頂点番号)

void copy(char a[][MAX_W], char b[][MAX_W]) {
	int i, j;
	rep(i, h)
		rep(j, w)
		a[i][j] = b[i][j];
}

void showBoard(char a[][MAX_W]) {
	int i, j;
	rep(i, h) {
		rep(j, w)
			printf("%c", a[i][j]);
		puts("");
	}
}

bool bfs(pair<pair<int, int>, int> start, int cnt) {
	pair<p, int> now;   //((現在のy座標,現在のx座標),現在の総距離)として保持。
	p temp;
	queue<pair<p, int> > q;
	q.push(start);
	board[start.first.first][start.first.second] = '.';   //呼び出し時のbfsの始点となった頂点は重複をなくすため、次回呼び出し時ではないものとして扱えばよい。
	copy(tmp, board);
	tmp[start.first.first][start.first.second] = 'x';
	//showBoard(tmp);
	//puts("");
	while (!q.empty()) {
		now = q.front(); q.pop();
		if (now.first.first + 1 < h && tmp[now.first.first + 1][now.first.second] != 'x') {
			if (tmp[now.first.first + 1][now.first.second] == '*') {
				adj[t[start.first]][t[temp = make_pair(now.first.first + 1, now.first.second)]] = now.second + 1;
				adj[t[temp]][t[start.first]] = now.second + 1;
				cnt--;
			}
			tmp[now.first.first + 1][now.first.second] = 'x';
			q.push(make_pair(make_pair(now.first.first + 1, now.first.second), now.second + 1));
		}
		if (now.first.first - 1 >= 0 && tmp[now.first.first - 1][now.first.second] != 'x') {
			if (tmp[now.first.first - 1][now.first.second] == '*') {
				adj[t[start.first]][t[temp = make_pair(now.first.first - 1, now.first.second)]] = now.second + 1;
				adj[t[temp]][t[start.first]] = now.second + 1;
				cnt--;
			}
			tmp[now.first.first - 1][now.first.second] = 'x';
			q.push(make_pair(make_pair(now.first.first - 1, now.first.second), now.second + 1));
		}
		if (now.first.second + 1 < w && tmp[now.first.first][now.first.second + 1] != 'x') {
			if (tmp[now.first.first][now.first.second + 1] == '*') {
				adj[t[start.first]][t[temp = make_pair(now.first.first, now.first.second + 1)]] = now.second + 1;
				adj[t[temp]][t[start.first]] = now.second + 1;
				cnt--;
			}
			tmp[now.first.first][now.first.second + 1] = 'x';
			q.push(make_pair(make_pair(now.first.first, now.first.second + 1), now.second + 1));
		}
		if (now.first.second - 1 >= 0 && tmp[now.first.first][now.first.second - 1] != 'x') {
			if (tmp[now.first.first][now.first.second - 1] == '*') {
				adj[t[start.first]][t[temp = make_pair(now.first.first, now.first.second - 1)]] = now.second + 1;
				adj[t[temp]][t[start.first]] = now.second + 1;
				cnt--;
			}
			tmp[now.first.first][now.first.second - 1] = 'x';
			q.push(make_pair(make_pair(now.first.first, now.first.second - 1), now.second + 1));
		}
		if (cnt == 0)
			return true;
	}
	return false;
}

void showAdj(int max) {
	int i, j;
	rep(i, max) {
		rep(j, max)
			printf("%3d ", adj[i][j]);
		puts("");
	}
}

int dfs(int max) {
	int i, j = 0, cnt = 0, min = MAX_H * MAX_W + 1;
	p now;
	Color color[MAX_A];
	stack<p> s;   //(番号、距離)で保持。
	rep(i, max)
		color[i] = WHITE;
	s.push(make_pair(0, 0));
	color[0] = BLACK;
	while (!s.empty()) {
		now = s.top();
		for (i = j; i < max; i++)
			if (color[i] == WHITE) {
				color[i] = BLACK;
				s.push(make_pair(i, now.second + adj[now.first][i]));
				//printf("%d %d\n", i, now.second + adj[now.first][i]);
				j = 0;
				break;
			}
		if (i == max) {
			if (s.size() == max && now.second < min) {
				min = now.second;
				//printf("min:%d\n", min);
			}
			j = now.first + 1;
			color[now.first] = WHITE;
			s.pop();
		}
	}
	return min;
}

int main() {
	int i, j, cnt, temp, sy, sx;
	bool flag;
	pair<pair<int, int>, int> z;
	map<pair<int, int>, int>::iterator it;
	while (1) {
		scanf("%d%d", &w, &h);
		if (!(h || w))
			break;
		cnt = 0;
		rep(i, h) {
			getchar();
			rep(j, w) {
				board[i][j] = getchar();
				if (board[i][j] == '*') {
					t[make_pair(i, j)] = cnt + 1;
					cnt++;
				}
				else if (board[i][j] == 'o') {
					t[make_pair(i, j)] = 0;
					sy = i; sx = j;
				}
			}
		}
		temp = cnt;   //汚れの数を保持。
//開始位置を始点とするbfsだけ先に行い、adj[0][j]とadj[i][0]の値を埋める。
		flag = true;
		z.first.first = sy; z.first.second = sx; z.second = 0;
		if (!bfs(z, cnt))
			flag = false;
		else
			cnt--;
//順番に汚れの座標を始点とするbfsを行い、残りの隣接行列adjの値を埋める。
		for (it = t.begin(); flag && cnt > 0 && it != t.end(); it++) {
			if (sy == it->first.first && sx == it->first.second)
				continue;
			z.first = it->first;z.second = 0;
			if (!bfs(z, cnt))
				break;
			cnt--;
		}
		if (cnt == 0) {
			//showAdj(temp + 1);
			printf("%d\n", dfs(temp + 1));
		}
		else
			puts("-1");
		t.clear();
	}
	return 0;
}