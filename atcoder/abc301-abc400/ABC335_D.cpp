/*アルゴリズムと工夫点(Loong and Takahashi/CPU: 1 ms  Memory: 3932 KB  Length: 697 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 45
#define MAX_D 4
#define NIL 0
using namespace std;

int n, mmap[MAX_N][MAX_N] = { 0 }, dx[MAX_D] = { 1,0,-1,0 }, dy[MAX_D] = { 0,1,0,-1 };

int main() {
	int i = 0, j = 1, y = 0, x = 0;
	scanf("%d",&n);
	while (j < n * n) {
		mmap[y][x] = j++;
		if (y + dy[i] < 0 || y + dy[i] >= n || x + dx[i] < 0 || x + dx[i] >= n || mmap[y+dy[i]][x+dx[i]] != NIL)
			i = (i + 1) % MAX_D;
		y += dy[i];
		x += dx[i];
	}
	rep(i, n) {
		rep(j, n-1) {
			if (i == (n - 1) / 2 && j == (n - 1) / 2)
				printf("T ");
			else
				printf("%d ",mmap[i][j]);
		}
		printf("%d\n", mmap[i][j]);
	}
	return 0;
}