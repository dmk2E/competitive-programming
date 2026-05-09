/*アルゴリズムと工夫点(Curling 2.0/CPU: 100 ms  Memory: 54908 KB  Length: 3137 B)
盤面の状態をmapを用いて保持しておくことで、同じ状態を生成されないようにしておいて、幅優先探索を行った。しかし、複数のルートで同じ状態になることはほとんどないと考えられ、する必要はなかったと考えられる(しない方が高
速)。盤面の状態は、二次元配列を一次元配列に直したstringで保持した。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_H 20
#define MAX_W 20
#define MAX_CNT 10
#define MAX_D 4
#define NIL -1
using namespace std;

typedef struct data {
	int y, x, cnt;
	string mp;
}Data;

int w, h;

int searchMin(Data now) {
	int i;
	map<string, bool> check;
	queue<Data> que;
	Data temp;
	que.push(now);
	check[now.mp] = true;
	while (!que.empty()) {
		now = que.front(); que.pop();
		if (now.cnt >= 10)
			continue;
		//cout << "now:" << now.mp << endl;
		now.cnt++;
		if (now.y+1<h&&now.mp[(now.y + 1) * w + now.x] != '1') {
			temp = now;
			temp.mp[temp.y * w + temp.x] = '0';
			i = 1;
			while (temp.y+i<h&&temp.mp[(temp.y + i)*w + temp.x] != '1') {
				if (temp.mp[(temp.y + i) * w + temp.x] == '3')
					return temp.cnt;
				i++;
			}
			if (temp.y + i < h) {
				temp.mp[(temp.y + i) * w + temp.x] = '0';
				temp.mp[(temp.y + i-1) * w + temp.x] = '2';
				if (check[temp.mp] == false) {
					check[temp.mp] = true;
					temp.y = temp.y + i - 1;
					que.push(temp);
				}
			}
		}
		//puts("↓");
		if (now.y-1>=0&&now.mp[(now.y - 1) * w + now.x] != '1') {
			temp = now;
			temp.mp[temp.y * w + temp.x] = '0';
			i = -1;
			while (temp.y + i >= 0 && temp.mp[(temp.y + i) * w + temp.x] != '1') {
				if (temp.mp[(temp.y + i) * w + temp.x] == '3')
					return temp.cnt;
				i--;
			}
			if (temp.y + i >= 0) {
				temp.mp[(temp.y + i) * w + temp.x] = '0';
				temp.mp[(temp.y + i + 1) * w + temp.x] = '2';
				if (check[temp.mp] == false) {
					check[temp.mp] = true;
					temp.y = temp.y + i + 1;
					que.push(temp);
				}
			}
		}
		//puts("↑");
		if (now.x+1<w&&now.mp[now.y * w + now.x+1] != '1') {
			temp = now;
			temp.mp[temp.y * w + temp.x] = '0';
			i = 1;
			while (temp.x + i < w && temp.mp[temp.y * w + temp.x+i] != '1') {
				if (temp.mp[temp.y * w + temp.x+i] == '3')
					return temp.cnt;
				i++;
			}
			if (temp.x + i < w) {
				temp.mp[temp.y * w + temp.x + i] = '0';
				temp.mp[temp.y * w + temp.x + i - 1] = '2';
				if (check[temp.mp] == false) {
					check[temp.mp] = true;
					temp.x = temp.x + i - 1;
					que.push(temp);
				}
			}
		}
		//puts("→");
		if (now.x-1>=0&&now.mp[now.y * w + now.x - 1] != '1') {
			temp = now;
			temp.mp[temp.y * w + temp.x] = '0';
			i = -1;
			while (temp.x + i >= 0 && temp.mp[temp.y * w + temp.x + i] != '1') {
				if (temp.mp[temp.y * w + temp.x + i] == '3')
					return temp.cnt;
				i--;
			}
			if (temp.x + i >= 0) {
				temp.mp[temp.y * w + temp.x + i] = '0';
				temp.mp[temp.y * w + temp.x + i + 1] = '2';
				if (check[temp.mp] == false) {
					check[temp.mp] = true;
					temp.x = temp.x + i + 1;
					que.push(temp);
				}
			}
		}
		//puts("←");
		//printf("check:%u\n",check.size());
	}
	return NIL;
}

int main() {
	int i, j, tmp;
	char str[MAX_H * MAX_W + 1];
	Data temp;
	while (1){
		scanf("%d%d", &w, &h);
		if (!(w || h))
			break;
		rep(i,h)
			rep(j, w) {
				scanf("%d",&tmp);
				str[i * w + j] = (char)(tmp + (int)'0');
				if (tmp == 2) {
					temp.y = i;
					temp.x = j;
				}
			}
		temp.cnt = 0;
		str[h * w] = '\0';
		temp.mp = string(str);
		printf("%d\n",searchMin(temp));
	}
	return 0;
}