/*アルゴリズムと工夫点(The Genome Database of All Space Life/CPU: 0 ms  Memory: 3324 KB  Length: 2726 B)
与えられたs上で、()で囲われた文字列を「部分文字列」とする。また、main関数内で着目している文字列は、()で囲われていない文字列とする(初めはs)。
sを先頭から訪問していき、途中でx番目の文字が現れたら、その文字を出力する。途中で'('が登場した場合、それと対となる')'との間に存在する部分文字列の長さ(もし「3(ABC)D」なら「ABCABCABCD」となるから長さは「10」となる)を
cal関数で計算し、その()の係数も考慮したうえで、その部分文字列内にx番目の文字が存在しないなら、')'の次の文字から訪問を再開する。存在するなら、着目する文字列をその部分文字列に更新し、以降同様の処理をする。更新する際、
x,bbgnの値の更新をきちんと行うこと(xの値は単純にxを部分文字列の長さで割った余りとなる)。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_ALFA 26
#define MAX_S 100
#define NIL -1
using namespace std;

typedef struct keisu {   //keta:桁数 value:値
	int keta, value;
}Keisu;

int x;
Keisu K[MAX_S];
char s[MAX_S+1],alfa[MAX_ALFA+1]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool isAlfa(char c) {   //文字コードの規格によっては、'A'～'Z'の文字コードは連続しないため、この関数を用意。
	int i;
	rep(i, MAX_ALFA)
		if (c == alfa[i])
			return true;
	return false;
}

int cal(int& bgn) {   //()で囲まれた文字列の添え字[bgn,end]とし、()内の文字列の数を返す。ただしxを超える値の場合、必ずその中に存在するから、「-1」を返す。実装を楽にするため、再帰関数を利用する。
	int sum = 0, seki = 1, temp;
	//printf("[%d,",bgn);
	while (1) {
		if (s[++bgn] == '(') {
			if ((temp = cal(bgn)) == NIL)
				return NIL;
			sum += seki*temp;
			seki = 1;
		}
		else if (s[bgn] == ')')
			break;
		else if ((int)'0' <= (int)s[bgn] && (int)s[bgn] <= (int)'9') {
			seki = K[bgn].value;
			bgn += K[bgn].keta - 1;
		}
		else {
			sum += seki;
			seki = 1;
		}
		if ((long long)x < sum)
			return NIL;
		//printf(" sum:%d ",sum);
	}
	//printf("%d]\n",bgn);
	return sum;
}

int main() {
	int i, j, bbgn, seki,tmp;   //bbgn:s[i]の現在の全体の文字列上のインデックス seki:現在着目している文字列中の部分文字列の係数
	while (1) {
		scanf("%s%d",s,&x);
		if (s[0] == '0' && x == 0)
			break;
		for (i = 0; s[i] != '\0'; i++) {   //Kの初期化
			if((int)'0' <= (int)s[i] && (int)s[i] <= (int)'9'){
				tmp = i;
				j = 0;
				while ((int)'0' <= (int)s[i] && (int)s[i] <= (int)'9') {
					j *= 10;
					j += (int)s[i++] - (int)'0';
				}
				K[tmp].keta = i - tmp; K[tmp].value = j;
				i--;
			}
		}
		j = 0;
		/*
		for (i = 0;s[i]!='\0'; i++) {   //cal関数のテスト
			if (s[i] == '(') {
				j = i;
				printf("%d:%d\n", i, cal(j));
			}
		}
		*/
		for (i = bbgn = 0, seki = 1; s[i] != '\0';) {
			if((int)'0' <= (int)s[i] && (int)s[i] <= (int)'9') {
				seki *= K[i].value;
				i += K[i].keta;
			}
			else if (isAlfa(s[i])) {
				tmp = bbgn + seki - 1;
				//printf("tmp:%d\n",tmp);
				if (x <= tmp) {
					printf("%c\n",s[i]);
					break;
				}
				bbgn = tmp + 1;
				i++;
				seki = 1;
			}
			else if (s[i] == '(') {
				tmp = i;
				j = cal(tmp);
				if (j == NIL) {
					i++;
				}
				else if (x < bbgn+seki * j) {
					i++;
					x = (x - bbgn) % j;
					bbgn = 0;
				}
				else {
					i = tmp + 1;
					bbgn += seki * j;
				}
				seki = 1;
			}
			//printf("i:%d bbgn:%d x:%d seki:%d j:%d\n",i,bbgn,x,seki,j);
		}
		if (s[i] == '\0')
			puts("0");
	}
	return 0;
}