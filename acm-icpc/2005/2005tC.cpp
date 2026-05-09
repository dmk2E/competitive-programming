/*アルゴリズムと工夫点(Dragon Fantasy/CPU: 100 ms  Memory: 3344 KB  Length: 1279 B)
勇者の位置とクリスタルの位置を頂点とみなした無向完全グラフを作成し、深さ優先探索を行った。勇者の初めの位置の頂点番号を0とし、クリスタルの各位置を入力された順に頂点1,2,...nとした。n=20だから枝刈りを行った。
枝刈り条件は「現在位置から取ることができないクリスタルが1つでもあるなら、探索を打ち切る」というもの(∵頂点a,b,cがある時、三角形の成立条件より、ab<ac+cbが成立することから現在の頂点aとして、a->bが無理ならa->c->b
というルートも不可能となるから)。

・ユークリッド距離は2点間の直線距離のことで、マンハッタン距離は各座標の差の絶対値の総和を表す。
・計算量が階乗となる探索問題の解法
10!以下->全探索　20!->枝刈り探索　50!->通常の探索では解けない(DPで解くことが多い)
全探索を高速化する手法の一つに「枝刈り」がある。これは探索対象を木構造だとみなし、途中の深さで探索を打ち止める条件を付けることにより、より高速化する手法で、木構造の深さが浅いうちに探索を打ち切れるような枝刈り
条件が望ましい。
・浮動小数点型の値の等価演算は、内部の値の保持の方法の関係で本来の値と微小な差が生まれてしまい、正確に行うことができない。そのため等しいと判定する方法の一つとして、「差の値が非常に小さい値以下ならば等価とする」
という方法があり、今回はそれを用いて魔王の瘴気の円周上にクリスタルがあるか判定した。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_N 20
#define INF 8000001
#define EPS (1e-10)
using namespace std;

typedef enum color {
	BLACK=-2,
	WHITE
}Color;

typedef pair<int, int> p;

int n, dx, dy;
double adj[MAX_N + 1][MAX_N + 1], tlmt[MAX_N + 1];   //tlmt[i]は頂点iは時間tlmt[i]までに到達しないと、瘴気で取れなくなってしまうことを示している。
Color color[MAX_N + 1];
p idx[MAX_N + 1];

bool dfs(double t,int now,int cnt) {
	int i;
	if (cnt == n + 1)
		return true;
	rep(i, n + 1) {
		if (color[i] == WHITE&&tlmt[i]<=t+adj[now][i]+EPS)
			return false;
	}
	rep(i, n + 1) {
		if (color[i] == WHITE) {
			color[i] = BLACK;
			if(dfs(t+adj[now][i],i,cnt+1))
				return true;
			color[i] = WHITE;
		}
	}
	return false;
}

double dist(int x,int y) {
	return sqrt(x*x+y*y);
}

int main() {
	int i, j;
	while (1) {
		cin >> n >> idx[0].first >> idx[0].second >> dx >> dy;
		if (!(n || idx[0].first || idx[0].second || dx || dy))
			break;
		rep(i, n)
			cin >> idx[i+1].first >> idx[i+1].second;
		rep(i, n+1) {
			adj[i][i] = INF;
			color[i] = WHITE;
			tlmt[i] = dist(idx[i].first - dx,idx[i].second - dy);
			for (j = i + 1; j < n+1; j++) 
				adj[i][j] = adj[j][i] = dist(idx[i].first - idx[j].first,idx[i].second-idx[j].second);
		}
		color[0] = BLACK;
		if (dfs(0.0,0,1))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}