/*アルゴリズムと工夫点(ぐらぐら/CPU: 0 ms  Memory: 3220 KB  Length: 4049 B)
全てのピースについて簡易診断を満たすかどうか判定する。この時、全ピース数は60*10=600未満であるあるから、最悪計算量は600^2<10^6となり十分高速。従って簡易診断をするためのデータを以下の手順で作成していく。
①同じ数字を持つ異なる2つのピースがありうる場合が考えられるため、標準入力された状態を保持したchar型配列tempを、それぞれのピースに一意に定まる番号を付けたint型配列mmapに変換する。この時、'.'はNILとした。番号の付
け方は領域の塗りつぶしと同じ原理でdfsで実装した。
※ここで、mmap[i][j]にブロックが存在する場合、そのブロック左端と右端それぞれのx座標はj,j+1となるから重心のx座標は(j+j+1)/2=(2*j+1)/2となる。従ってピースの重心は、ピースを構成する全てのブロックの重心を足し合わせて
、全ブロック数である4を割ったものとなる。
ここで、
p[x]:一意に定まる識別番号xを持つピースの(xL,xR,xG)を保持するデータ構造。
adj[x]:識別番号がxであるピースが直接、または間接的に支えているピースの識別番号を保持する。
②bfsをベースにして各ピースのxL,xR,xGを求めると同時に、「下面」に接している別のピースを探索し、adjに追加。配列pは完成する。
③dfsを元にして、adjを完成させる。
④pとadjを元に一つ一つのピースに対して簡易診断を行って判定する。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_W 10
#define MAX_H 60
#define MAX_P 600
#define NIL -1
#define NNIL (int)'#'
#define EPS (1e-10)
using namespace std;

typedef struct piece {
	int xL, xR;
	double xG;

	piece(int xxL=0,int xxR=0,double xxG=0):xL(xxL),xR(xxR),xG(xxG){}
}Piece;

int w, h, mmap[MAX_H][MAX_W], pp;
char temp[MAX_H][MAX_W + 1];
Piece p[MAX_P];

void coloring(int y, int x, char c) {   //dfsで番号を振っていく。
	temp[y][x] = (char)NNIL;
	mmap[y][x] = pp;
	if (y + 1 < h && temp[y + 1][x] == c) {
		coloring(y + 1, x, c);
	}
	if (y - 1 >= 0 && temp[y - 1][x] == c) {
		coloring(y - 1, x, c);
	}
	if (x + 1 < w && temp[y][x + 1] == c) {
		coloring(y, x + 1, c);
	}
	if (x - 1 >= 0 && temp[y][x - 1] == c) {
		coloring(y, x - 1, c);
	}
}

void makeMap() {   //①の処理
	int i, j;
	rep(i, h) {
		rep(j, w) {
			if (temp[i][j] == (char)NNIL)
				continue;
			if (temp[i][j] == '.') {
				temp[i][j] = (char)NNIL;
				mmap[i][j] = NIL;
			}
			else {
				coloring(i, j, temp[i][j]);
				pp++;
			}
		}
	}
}

bool bfs(int y,int x,bool flag[MAX_H][MAX_W],vector<int> adj[MAX_P]) {
	int f = mmap[y][x], xMin = p[f].xL = MAX_W + 2, xMax = p[f].xR = -1, sum = 0;
	pair<int, int> now;
	bool ff=true,fff=false;
	queue<pair<int, int> > que;
	flag[y][x] = true;
	que.push(make_pair(y, x));
	while (que.size()) {
		now = que.front(); que.pop();
		sum += now.second * 2 + 1;
		if (now.first + 1 == h) {   //下面が地面に接している時の処理
			if (p[f].xL > now.second)
				p[f].xL = now.second;
			if (p[f].xR < now.second + 1)
				p[f].xR = now.second + 1;
			fff = true;
		}
		if (now.first + 1 < h && mmap[now.first + 1][now.second] != NIL && mmap[now.first + 1][now.second] != f) {//下面に別のピースが接している時の処理
			if (p[f].xL > now.second)
				p[f].xL = now.second;
			if (p[f].xR < now.second + 1)
				p[f].xR = now.second + 1;
			if (ff) {
				adj[mmap[now.first + 1][now.second]].push_back(f);
				ff = false;
			}
		}
		if (now.first + 1 < h && mmap[now.first + 1][now.second] == f && flag[now.first + 1][now.second] == false) {
			flag[now.first + 1][now.second] = true;
			que.push(make_pair(now.first + 1, now.second));
		}
		if (now.first - 1 >= 0 && mmap[now.first - 1][now.second] == f && flag[now.first - 1][now.second] == false) {
			flag[now.first - 1][now.second] = true;
			que.push(make_pair(now.first - 1, now.second));
		}
		if (now.second + 1 < w && mmap[now.first][now.second + 1] == f && flag[now.first][now.second + 1] == false) {
			flag[now.first][now.second + 1] = true;
			que.push(make_pair(now.first, now.second + 1));
		}
		if (now.second - 1 >= 0 && mmap[now.first][now.second - 1] == f && flag[now.first][now.second - 1] == false) {
			flag[now.first][now.second - 1] = true;
			que.push(make_pair(now.first, now.second - 1));
		}
	}
	p[f].xG = (double)sum / 8;
	return true;
}

void showMap() {
	int i, j;
	rep(i, h) {
		rep(j, w)
			printf("%3d", mmap[i][j]);
		puts("");
	}
}

void makeAdj(vector<int>& now, int nnow, vector<int> adj[MAX_P], bool flag[MAX_P]) {
	int i;
	for (int x : adj[nnow]) {
		if (flag[x] == false) {
			flag[x] = true;
			now.push_back(x);
			makeAdj(now, x, adj, flag);
		}
	}
}

bool judge() {
	int i, j;
	double temp;
	bool flag[MAX_H][MAX_W] = { 0 };
	vector<int> adj[MAX_P];
	//showMap();
	rep(i, h) {   //②の処理
		rep(j, w) {
			if (flag[i][j] == false) {
				if (mmap[i][j] == NIL)
					flag[i][j] = true;
				else {
					if (bfs(i, j, flag, adj) == false)
						return false;
				}
			}
		}
	}
	rep(i, pp) {   //③の処理
		bool fflag[MAX_P] = { 0 };
		fflag[i] = true;
		vector<int> v;
		for (int x : adj[i]) {
			fflag[x] = true;
			makeAdj(v, x, adj, fflag);
		}
		for (int x : v)
			adj[i].push_back(x);
	}
	/*
	rep(i, pp) {	//実装が上手くいっているかのデバック出力
		printf("%d(%d,%d,%f):", i, p[i].xL, p[i].xR, p[i].xG);
		for (int x : adj[i])
			printf("->%d", x);
		puts("");
	}
	*/
	rep(i, pp) {   //④の処理
		temp = p[i].xG;
		for (int x : adj[i]) {
			temp += p[x].xG;
		}
		temp /= (adj[i].size() + 1);
		if (fabs(p[i].xL - temp) < EPS || fabs(p[i].xR - temp) < EPS || p[i].xL > temp || temp > p[i].xR)
			return false;
	}
	return true;
}

int main() {
	int i, j;
	while (1) {
		scanf("%d%d", &w, &h);
		if (!(w || h))
			break;
		pp = 0;
		rep(i, h)
			scanf("%s", temp[i]);
		makeMap();

		if (judge())
			puts("STABLE");
		else
			puts("UNSTABLE");
	}
	return 0;
}