/*アルゴリズムと工夫点(Loong Tracking/CPU: 238 ms  Memory: 11688 KB  Length: 1185 B)
数字の文字コードの連続性を利用して文字を数値に変換する方法は、その値が0～9の1桁の時しかできない。
最悪計算量はO(n+q)となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1000000
using namespace std;

typedef struct data {
	int x, y;

	data(int a = 0, int b = 0) {
		x = a;
		y = b;
	}
}Data;

int n, q;
Data parts[MAX_N];

int search(int head,int tail,int num) {
	if (head + num - 1 <= n - 1)
		return head + num - 1;
	return num - (n - head) - 1;
}

int main() {
	int i, head, tail, j;
	string c;
	scanf("%d%d",&n,&q);
	rep(i, n)
		parts[i] = Data(i + 1, 0);
	head = 0; tail = n - 1;
	while (q--) {
		scanf("%d",&i);
		if (i == 1) {
			cin >> c;
			switch (c[0]) {
				case 'R':
					parts[tail] = Data(parts[head].x + 1, parts[head].y);
					break;
				case 'L':
					parts[tail] = Data(parts[head].x - 1, parts[head].y);
					break;
				case 'U':
					parts[tail] = Data(parts[head].x, parts[head].y + 1);
					break;
				default:
					parts[tail] = Data(parts[head].x, parts[head].y - 1);
					break;
			}
			head = head - 1 < 0 ? n - 1 : head - 1;
			tail = tail - 1 < 0 ? n - 1 : tail - 1;
		}
		else {
			cin >> j;
			i = search(head, tail, j);
			printf("%d %d\n", parts[i].x, parts[i].y);
		}
	}
	return 0;
}