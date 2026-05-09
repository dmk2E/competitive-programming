/*アルゴリズムと工夫点(土地囲い/CPU: 0 ms  Memory: 3632 KB  Length: 1556 B)
bfsで領域の塗りつぶしを行うイメージで土地の大きさを数え上げる。各マスを節点とすると、各節点は辺を最大4つ持つ無向グラフを見なせるため、最悪計算量は、O((h*w+h*w*4)*2)<10^5 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 50
#define MAX_W 50
using namespace std;

int w, h;
char mmap[MAX_H][MAX_W + 1];
bool flag[MAX_H][MAX_W];   //一度訪れたマスを二度と訪れないようにするためのマーカー

void initFlag() {
	int i, j;
	rep(i, h)
		rep(j, w)
			flag[i][j] = true;
}

bool isAdj(int y, int x, int& cnt, char c) {   //範囲外のマスに隣接している場合、そのマスは拡大隣接しているとみなす処理を行っているため、範囲外のマスだけに囲われている場合も拡大隣接しているとみなしてしまう。
	if (mmap[y][x] == c)
		return true;
	else if (mmap[y][x] != '.')
		return false;
	flag[y][x] = false;
	if ((y + 1 >= h || flag[y + 1][x] == false || isAdj(y + 1, x, cnt, c)) & (y - 1 < 0 || flag[y - 1][x] == false || isAdj(y - 1, x, cnt, c)) & (x + 1 >= w || flag[y][x + 1] == false || isAdj(y, x + 1, cnt, c)) & (x - 1 < 0 || flag[y][x - 1] == false || isAdj(y, x - 1, cnt, c))) {//短絡評価にならないように'&'を使用
		cnt++;
		return true;
	}
	cnt = 0;
	return false;
}

int main() {
	int i, j, cntW, cntB, tmp;
	while (1) {
		scanf("%d%d", &w, &h);
		if (!(w || h))
			break;
		cntW = cntB = 0;
		rep(i, h) {
			getchar();
			rep(j, w) {
				scanf("%c", &mmap[i][j]);
				if (mmap[i][j] == 'W')
					cntW++;
				else if (mmap[i][j] == 'B')
					cntB++;
			}
		}
		if (cntW > 0) {
			initFlag();
			cntW = 0;
			rep(i, h)
				rep(j, w)
					if (flag[i][j] && mmap[i][j] == '.') {
						tmp = 0;
						isAdj(i, j, tmp, 'W');
						cntW += tmp;
						//printf("(%d,%d):%d\n", i, j, cntW);
					}
		}
		if (cntB > 0) {
			initFlag();
			cntB = 0;
			rep(i, h)
				rep(j, w)
					if (flag[i][j] && mmap[i][j] == '.') {
						tmp = 0;
						isAdj(i, j, tmp, 'B');
						cntB += tmp;
						//printf("(%d,%d):%d\n", i, j, cntB);
					}
		}
		printf("%d %d\n", cntB, cntW);
	}
	return 0;
}