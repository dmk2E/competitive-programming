/*アルゴリズムと工夫点(Organize Your Train part II/CPU: 10 ms  Memory: 3516 KB  Length: 1149 B)
作ることができる文字列の種類数が分かればいいから、連想コンテナのset<string>を用いる。全ての2つへの分割パターンに対し、それぞれ並びを反転させる否か、前車両か後ろ車両にかによって作成される文字列が異なり、作られる
文字列の種類数を全探索して求める。最悪計算量は、O(len*(len+2*2*2*len))<10^5 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_S 72
using namespace std;

int m;
char train[MAX_S+1];
set<string> logger;

void combine(char *a,char *b,char *c,int len) {
	int i=0,j=0,k;
	rep(k, len) {
		if (a[i] != '\0')
			c[k] = a[i++];
		else
			c[k] = b[j++];
	}
	c[k] = '\0';
}

void reverse(char *a) {
	int i,j;
	char b[MAX_S + 1];
	for (i = 0;a[i]!='\0'; i++)
		b[i] = a[i];
	b[i] = a[i];
	rep(j, i)
		a[j] = b[i - j - 1];
}

int main() {
	int i, j, len;
	string str;
	char a[MAX_S + 1], b[MAX_S + 1], c[MAX_S + 1];
	cin >> m;
	while (m--) {
		//scanf_s("%s",train,MAX_S+1);
		scanf("%s", train);
		len = strlen(train);
		rep(i, len-1) {
			rep(j, i + 1)
				a[j] = train[j];
			a[j] = '\0';
			for (j = i + 1; j < len; j++)
				b[j - i - 1] = train[j];
			b[j-i-1] = '\0';
			//printf("%s+%s\n",a,b);
			rep(j, 4) {
				combine(a, b, c, len);
				logger.insert(string(c));
				//cout << c << endl;
				combine(b, a, c, len);
				logger.insert(string(c));
				//cout << c << endl;
				if (j % 2 == 0)
					reverse(a);
				else
					reverse(b);
			}
		}
		printf("%d\n",logger.size());
		logger.clear();
	}
	return 0;
}