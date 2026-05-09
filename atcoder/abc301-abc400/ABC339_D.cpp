/*アルゴリズムと工夫点(Synchronized Players/CPU: 1693 ms  Memory: 553152 KB  Length: 2256 B)
幅優先探索では、最短距離を「既に生成した状態」を記録する表に入れることで、queueに保持する変数を減らすことができる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 60
#define MAX_D 4
using namespace std;

typedef struct data {
	int sum, y1, x1, y2, x2;
	string mmap;
}Data;

int n, dy[MAX_D] = { -1,0,1,0 }, dx[MAX_D] = { 0,1,0,-1 };

void showMap(string mp) {
	int i, j;
	rep(i, n) {
		rep(j, n)
			printf("%c", mp[i * n + j]);
		puts("");
	}
	puts("");
}

int bfs(Data now) {
	int i;
	Data temp;
	queue<Data> que;
	bool v[MAX_N][MAX_N][MAX_N][MAX_N];
	v[now.y1][now.x1][now.y2][now.x2] = true;
	que.push(now);
	while (que.size()) {
		now = que.front(); que.pop();
		//printf("sum:%d,(%d,%d),(%d,%d)\n", now.sum, now.y1, now.x1, now.y2, now.x2);
		//showMap(now.mmap);
		if (now.y1 == now.y2 && now.x1 == now.x2)
			return now.sum;
		now.sum++;
		for (i = 0; i < MAX_D; i++) {
			temp = now;
			if (temp.y1 + dy[i] >= 0 && temp.y1 + dy[i] < n && temp.x1 + dx[i] >= 0 && temp.x1 + dx[i] < n&&temp.mmap[(temp.y1 + dy[i])*n+ temp.x1 + dx[i]]!='#') {
				if (temp.y2 != temp.y1 || temp.x1 != temp.x2)
					temp.mmap[temp.y1 * n + temp.x1] = '.';
				temp.y1 += dy[i];
				temp.x1 += dx[i];
				temp.mmap[temp.y1 * n + temp.x1] = 'P';
				//showMap(temp.mmap);
			}
			if (temp.y2 + dy[i] >= 0 && temp.y2 + dy[i] < n && temp.x2 + dx[i] >= 0 && temp.x2 + dx[i] < n && temp.mmap[(temp.y2 + dy[i]) * n + temp.x2 + dx[i]] != '#') {
				if(temp.y2!=temp.y1||temp.x1!=temp.x2)
					temp.mmap[temp.y2 * n + temp.x2] = '.';
				temp.y2 += dy[i];
				temp.x2 += dx[i];
				temp.mmap[temp.y2 * n + temp.x2] = 'P';
				//showMap(temp.mmap);
			}
			if (v[temp.y1][temp.x1][temp.y2][temp.x2] == false) {
				v[temp.y1][temp.x1][temp.y2][temp.x2] = true;
				que.push(temp);
			}
		}
	}
	return -1;
}

int main() {
	int i, j;
	bool flag = true;
	char temp;
	Data first;
	first.sum = 0;
	scanf("%d", &n);
	rep(i, n) {
		getchar();
		rep(j, n) {
			temp = getchar();
			first.mmap += temp;
			if (temp == 'P') {
				if (flag) {
					first.y1 = i;
					first.x1 = j;
					flag = false;
				}
				else {
					first.y2 = i;
					first.x2 = j;
				}
			}
		}
	}
	//printf("%d %d %d %d\n", first.y1, first.x1, first.y2, first.x2);
	printf("%d\n", bfs(first));
	return 0;
}

/*
	data(int ssum = 0, int yy1 = 0, int xx1 = 0, int yy2 = 0, int xx2 = 0,string mmmap) {
		sum = ssum;
		y1 = yy1;
		x1 = xx1;
		y2 = yy2;
		x2 = xx2;
		mmap = mmmap;
	}
*/