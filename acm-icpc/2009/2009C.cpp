/*アルゴリズムと工夫点(覆面算/CPU: 880 ms  Memory: 3448 KB  Length: 3406 B)
単純に全探索する場合、最大10種類の文字に対して異なる数字を割り当てることになるから、10!<10^7 となるが、割り当てた後に最大8*12個の文字を訪問し、処理をするため、最悪計算量が10^8を超えてしまう可能性がある。その場合、一つのファイル
にある複数のデータを処理する必要があることを考慮すると、一つのファイルにある入力に対する出力を出すまでに、1分以上かかってしまう可能性がある。
そこで、枝狩り探索を行う。与えられた各文字列S1,S2,S3,,,Sn-1 の下位の桁の文字にそれぞれ数字を割り当て、その「次の桁への繰り上がりを無視した和」がSnの対応する桁の文字に割り当てた数字と一致するか、または一致するように割り当てること
ができるかを判定し、出来なければ、各文字列S1,S2,S3,,,Sn-1　の数字の割り当てをやり直すようにする。つまり、「S1+S2+S3+...+Sn-1」の和の各桁が、Snの各桁の値と一致するように割り当てることが可能かを、下の桁から判定していく。こうする
ことで、途中の桁で上手く割り当てることができなければ、その時点でその探索の枝刈りを行えるため、十分高速に動作する。このような動的な動作を行うのに、再帰関数は便利。

*問題文を勘違いしてしまったため、"2AB5"のような数値があらかじめ決まっている桁が存在する文字列が与えられる場合にも対応したコードとなっている。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 12
#define MAX_NUM 10
#define HEAD 1
#define EXIST 0
#define NIL -1
using namespace std;

int n,maxL;
string str[MAX_N];
map<char, int> v,nnum;   //nnum:アルファベットに対して、割り当てられた数字を返す。

int dfs(int y,int x,int c,bool num[]) {   //y行目の文字列について、末端からx文字目,その桁の合計値c,どの数字を使ったか保持するnum
	int cnt = 0, i;
	if (y == n - 1) {
		if (x == maxL - 1) {
			if ((int)'0' <= (int)str[y][str[y].length() - 1 - x] && (int)str[y][str[y].length() - 1 - x] <= (int)'9') {
				return (int)str[y][str[y].length() - 1 - x] - (int)'0' == c ? 1 : 0;
			}
			else if (nnum[str[y][str[y].length() - 1 - x]] != NIL) {
				return nnum[str[y][str[y].length() - 1 - x]] == c ? 1 : 0;
			}
			else {
				if (c < 10&&num[c]) {
					if (c== 0)
						return v[str[y][str[y].length() - 1 - x]] == HEAD ? 0 : 1;
					else
						return 1;
				}
				else
					return 0;
			}
		}
		else {
			if ((int)'0' <= (int)str[y][str[y].length() - 1 - x] && (int)str[y][str[y].length() - 1 - x] <= (int)'9') {
				return (int)str[y][str[y].length() - 1 - x] - (int)'0' == c % 10 ? dfs(0, x + 1, c / 10, num) : 0;
			}
			else if (nnum[str[y][str[y].length() - 1 - x]] != NIL) {
				return nnum[str[y][str[y].length() - 1 - x]] == c % 10 ? dfs(0, x + 1, c / 10, num) : 0;
			}
			else {
				if (num[c%10]) {
					if (c % 10 == 0) {
						if (v[str[y][str[y].length() - 1 - x]] == HEAD)
							return 0;
						num[c % 10] = false;
						nnum[str[y][str[y].length() - 1 - x]] = c % 10;
						i = dfs(0, x + 1, c / 10, num);
						nnum[str[y][str[y].length() - 1 - x]] = NIL;
						num[c % 10] = true;
					}
					else {
						num[c % 10] = false;
						nnum[str[y][str[y].length() - 1 - x]] = c % 10;
						i = dfs(0, x + 1, c / 10, num);
						nnum[str[y][str[y].length() - 1 - x]] = NIL;
						num[c % 10] = true;
					}
					return i;
				}
				else
					return 0;
			}
		}
	}
	if ((int)str[y].length() - 1 - x < 0)
		return dfs(y + 1, x, c, num);
	if ((int)'0' <= (int)str[y][str[y].length() - 1 - x] && (int)str[y][str[y].length() - 1 - x] <= (int)'9') {
		cnt += dfs(y + 1, x, c + (int)str[y][str[y].length() - 1 - x] - (int)'0', num);
	}
	else if (nnum[str[y][str[y].length() - 1 - x]] != NIL) {
		cnt += dfs(y + 1, x, c + nnum[str[y][str[y].length() - 1 - x]], num);
	}
	else {
		rep(i, 10) {
			if (num[i]) {
				if (i == 0) {
					if (v[str[y][str[y].length() - 1 - x]] == HEAD)
						continue;
					num[i] = false;
					nnum[str[y][str[y].length() - 1 - x]] = i;
					cnt += dfs(y + 1, x, c + i, num);
					nnum[str[y][str[y].length() - 1 - x]] = NIL;
					num[i] = true;
				}
				else {
					num[i] = false;
					nnum[str[y][str[y].length() - 1 - x]] = i;
					cnt += dfs(y + 1, x, c + i, num);
					nnum[str[y][str[y].length() - 1 - x]] = NIL;
					num[i] = true;
				}
			}
		}
	}
	return cnt;
}

int main() {
	int i, j;
	bool num[MAX_NUM];   //0～9のどの数字が使用済みか
	rep(i, MAX_NUM)
		num[i] = true;
	while (1) {
		scanf("%d", &n);
		if (!n)
			break;
		maxL = 0;
		rep(i, n) {
			cin >> str[i];
			if (maxL < str[i].length())
				maxL = str[i].length();
			rep(j, str[i].length()) {
				if ((int)'0' <= (int)str[i][j] && (int)str[i][j] <= (int)'9')
					continue;
				if (j == 0 && str[i].length() > 1)
					v[str[i][j]] = HEAD;
				if (v[str[i][j]] == NIL)
					v[str[i][j]] = EXIST;
			}
		}
		i = 0;
		for (pair<char, int> c : v) {
			nnum[c.first] = NIL;
		}
		printf("%d\n", (size_t)maxL == str[n - 1].length() ? dfs(0, 0, 0, num) : 0);
		v.clear();
		nnum.clear();
	}
	return 0;
}

/*

void show() {   //文字に割り当てた数字確かめ用
	for (pair<char, int> p : nnum) {
		printf("%c %d\n", p.first, p.second);
	}
	puts("");
}

//全探索で解こうとしたやつ

int isEqual() {
	return 1;
}

int dfs(int now,bool num[]) {
	if (alfa[now] == '\0') {
		int ii;

		for (ii = 0; alfa[ii] != '\0'; ii++) {
			printf("%d ", nnum[alfa[ii]]);
		}
		puts("");
		return isEqual();
	}
	int i, cnt = 0;
	rep(i, 10) {
		if (num[i]) {
			if (i == 0) {
				if (v[alfa[now]] == EXIST) {
					nnum[alfa[now]] = i;
					num[i] = false;
					cnt += dfs(now + 1, num);
					num[i] = true;
					nnum[alfa[now]] = NIL;
				}
			}
			else {
				nnum[alfa[now]] = i;
				num[i] = false;
				cnt += dfs(now + 1, num);
				num[i] = true;
				nnum[alfa[now]] = NIL;
			}
		}
	}
	return cnt;
}
*/