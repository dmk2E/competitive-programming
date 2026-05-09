/*アルゴリズムと工夫点(如何に汝を満足せしめむ？ いざ数え上げむ…/CPU: 0 ms  Memory: 3440 KB  Length: 2922 B)
文字列解析では、'('と')'で挟まれた文字列を一つの単位とし、その(文字列)の解を求める再帰関数solveを作るようにする。solve関数では着目している文字列内で、(文字列)を発見した場合、solve関数を再帰呼び出しし、(文字列)も一つの塊
と見なして処理を行っていく。solve関数は文字列Sに対して、最悪計算量O(|S|) となる。今回では、p,q,rの全パターンは27通りとなるから、全体の最悪計算量は、O(27*|MAX_S|)<10^4 となり十分高速。
*ある関数に渡す引数1で用いた変数を、他の引数の所で引数1の代入式を置いてしまうと上手く行かない時があるため、絶対にしないこと。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX 3
#define MAX_S 80
#define NIL -1
using namespace std;

int hitei[MAX] = { 2,1,0 }, seki[][MAX] = { {0,0,0},{0,1,1},{0,1,2} }, wa[][MAX] = { {0,1,2},{1,1,2},{2,2,2} };
char s[MAX_S + 1];

int toNum(char c,int p,int q,int r) {   //'0','1','2','P','Q','R'それぞれ1文字を対応する整数値に変換する関数。通常のswitch分ではbreak分が必要になる。
	if ((int)'0' <= (int)c && (int)c <= (int)'2')
		return c - (int)'0';
	switch (c) {
		case 'P':
			return p;
		case 'Q':
			return q;
		default:
			return r;
	}
}

int endSearch(int now) {   //s[now]=='('となるnowを返し、その'('と対応する')'の添え字を返す。
	int tmp = 1;
	while (tmp > 0) {
		if (s[++now] == '(')
			tmp++;
		else if (s[now] == ')')
			tmp--;
	}
	return now;
}

int solve(int ss, int e, int p, int q, int r) {   //s[ss]=='(',s[e]==')'となる括弧内部の式の計算結果を返す関数。
	int now, tmp, left = NIL, temp, cal = NIL;
	//printf("[%d,%d]\n", ss, e);
	for (now = ss + 1; now < e; now++) {
		if (s[now] == '-') {   //--...--() はここで処理する。-の影響を受けるのが一つの定数や変数だけではなく、論理式である場合もここで処理する。
			tmp = 1;
			while (s[++now] == '-')
				tmp = (tmp + 1) % 2;
			temp = now;
			if (tmp) {
				if (s[now] == '(')
					tmp = hitei[solve(now, temp = endSearch(now), p, q, r)];
				else
					tmp = hitei[toNum(s[now], p, q, r)];
			}
			else {
				if (s[now] == '(')
					tmp = solve(now, temp = endSearch(now), p, q, r);
				else
					tmp = toNum(s[now], p, q, r);
			}
			now = temp;
		}
		else if (s[now] == '(') {   //「-」がない論理式の処理
			temp = now;
			now = endSearch(now);
			tmp = solve(temp, now, p, q, r);
		}
		else if (s[now] == '+') {   //()内部の計算が+なのか*なのかを保持
			cal = 0;
			continue;
		}
		else if (s[now] == '*') {
			cal = 1;
			continue;
		}
		else
			tmp = toNum(s[now], p, q, r);   //1つの定数、変数だった場合の処理
		//printf("now:%d %d(%d,%d,%d)\n", now, tmp, p, q, r);
		if (left == NIL)   //被演算子の左側を保持
			left = tmp;
		else {
			if (cal == 0)
				return wa[left][tmp];
			else
				return seki[left][tmp];
		}
	}
	return left;   //単項演算だった場合
}

bool judge(int p,int q,int r) {
	int now, tmp, left = NIL, temp, cal;
	for (now = 0; s[now] != '\0'; now++) {
		if (s[now] == '-') {
			tmp = 1;
			while (s[++now] == '-')
				tmp = (tmp + 1) % 2;
			temp = now;
			if (tmp) {
				if (s[now] == '(')
					tmp = hitei[solve(now, temp = endSearch(now), p, q, r)];
				else
					tmp = hitei[toNum(s[now], p, q, r)];
			}
			else {
				if (s[now] == '(')
					tmp = solve(now, temp = endSearch(now), p, q, r);
				else
					tmp = toNum(s[now], p, q, r);
			}
			now = temp;
		}
		else if (s[now] == '(') {
			temp = now;
			now = endSearch(now);
			tmp = solve(temp, now, p, q, r);
		}
		else if (s[now] == '+') {
			cal = 0;
			continue;
		}
		else if (s[now] == '*') {
			cal = 1;
			continue;
		}
		else
			tmp = toNum(s[now], p, q, r);
		//printf("now:%d %d(%d,%d,%d)\n", now, tmp, p, q, r);
		if (left == NIL)
			left = tmp;
		else {
			if (cal == 0)
				return wa[left][tmp] == 2;
			else
				return seki[left][tmp] == 2;
		}
	}
	return left == 2;
}

int main() {
	int i, j, k, cnt;
	while (1) {
		scanf("%s", s);
		if (s[0] == '.')
			break;
		cnt = 0;
		rep(i,MAX)
			rep(j,MAX)
				rep(k, MAX)
					if (judge(i, j, k)){
						cnt++;
						//printf("%d %d %d\n", i, j, k);
					}
		printf("%d\n", cnt);
	}
	return 0;
}