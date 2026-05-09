/*アルゴリズムと工夫点(島はいくつある？/CPU: 0 ms  Memory: 3700 KB  Length: 762 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 50
#define MAX_W 50
#define GROUND 1
#define SEA 0
using namespace std;

int w, h, mmap[MAX_H][MAX_W];

void dfs(int y, int x) {
	int i, j;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (0 <= y + i && y + i < h && 0 <= x + j && x + j < w && mmap[y + i][x + j] == GROUND) {
				mmap[y + i][x + j] = SEA;
				dfs(y + i, x + j);
			}
		}
	}
}

int main() {
	int i, j, cnt;
	while (1) {
		scanf("%d%d", &w, &h);
		if (!(w || h))
			break;
		rep(i, h)
			rep(j, w)
				scanf("%d", &mmap[i][j]);
		cnt = 0;
		rep(i, h) {
			rep(j, w) {
				if (mmap[i][j] == GROUND) {
					mmap[i][j] = SEA;
					dfs(i, j);
					cnt++;
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}