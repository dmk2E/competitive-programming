/*アルゴリズムと工夫点(お姫様の日本語/CPU: 0 ms  Memory: 3492 KB  Length: 2543 B)
まず1回、文字列を線形的に走査して、拍の単位で区切る。今回その区切りは、配列mmolaで表す。配列mmolaでは、拍の先頭文字と対応する添え字の位置、その拍の単語数を入れ、それ以外の添え字では「-1」を入れ
て保持。その後、'i'と'u'、'a'と'o'について、問題文の1.,2.の条件にのみ当てはまる、無声化される母音にフラグを付けておく(配列ansで対応)。最後に、ansと文字列を走査して、
「母音が無声化されるのは最初の母音である場合、または直近の母音が無声化されなかった場合」の条件を満たさないが、「無声化されるフラグ」がついている1文字のフラグをなくし、フラグがついている1文字は()でくく
って、全体の文字列を出力すればよい。
最悪計算量はO(|s|)<10^3 となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_S 14
#define MAX_STR 100
#define MAX_M 5
#define MAX_B 5
#define NIL -1
using namespace std;

int mmola[MAX_STR];
string str;
bool ans[MAX_STR];
char musei[MAX_M + 1] = "ksthp",boin[MAX_B + 1] = "aiueo";

bool isMusei(char c) {
	int i;
	rep(i, MAX_M)
		if (musei[i] == c)
			break;
	return i < MAX_M;
}

bool isBoin(char c) {
	int i;
	rep(i, MAX_B)
		if (boin[i] == c)
			break;
	return i < MAX_B;
}

void mola(const char *s) {   //拍単位に区切るmmolaの作成
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		mmola[i] = NIL;
		ans[i] = false;
	}
	for (i = 0; s[i] != '\0';) {
		if (isBoin(s[i])) {
			mmola[i] = 1;   //長音または母音
			i++;
		}
		else {
			if (isBoin(s[i + 1])||(s[i] == 'n' && s[i + 1] == '\'')) {   //子音+母音 「撥音」
				mmola[i] = 2;
				i += 2;
			}
			else if (s[i] == s[i + 1] || s[i] == 'n') {   //促音 「撥音」
				mmola[i] = 1;
				i++;
			}
			else {   //「子音」+「y」+「母音」
				mmola[i] = 3;
				i += 3;
			}
		}
	}
	for (i = 0; false&&str[i] != '\0'; i++)
		printf("%d ", mmola[i]);
}

int main() {
	int i, j, last;
	bool flagA, flagO;   //直前の拍において、無声子音と共に母音'a'or'o'が現れたかを示す。
	while (1) {
		getline(cin, str);
		if (str[0] == '#')
			break;
		mola(str.c_str());
		for (i = 0, last = NIL, flagA = flagO = false; i < str.length(); i += mmola[i]) {   //1回のループで1つの拍を走査する。
			rep(j, mmola[i]) {
				if (str[i + j] == 'i' || str[i + j] == 'u') {
					if ((mmola[i] == 2 && isMusei(str[i + j - 1])) || (mmola[i] == 3 && isMusei(str[i + j - 2]))) {
						if (str[i + j + 1] == '\0' || isMusei(str[i + j + 1])) {
							ans[i + j] = true;
						}
					}
				}
				else if (str[i + j] == 'a') {
					flagO = false;
					if ((mmola[i] == 2 && isMusei(str[i + j - 1])) || (mmola[i] == 3 && isMusei(str[i + j - 2]))) {
						if (flagA)
							ans[last] = true;
						flagA = true;
						last = i + j;
						break;
					}
					else
						flagA = false;
				}
				else if (str[i + j] == 'o') {
					flagA = false;
					if ((mmola[i] == 2 && isMusei(str[i + j - 1])) || (mmola[i] == 3 && isMusei(str[i + j - 2]))) {
						if (flagO)
							ans[last] = true;
						flagO = true;
						last = i + j;
						break;
					}
					else
						flagO = false;
				}
			}
			if (j == mmola[i])
				flagA = flagO = false;
		}
		for (i = 0, flagA = true; i < str.length(); i++) {   //「母音が無声化されるのは最初の母音である場合、または直近の母音が無声化されなかった場合」の条件判定
			if (isBoin(str[i])) {
				if (ans[i]) {
					if (flagA == false) {
						ans[i] = false;
						flagA = true;
					}
					else
						flagA = false;
				}
				else
					flagA = true;
			}
		}
		rep(i, str.length()) {
			if (ans[i])
				printf("(%c)", str[i]);
			else
				printf("%c", str[i]);
		}
		puts("");
	}
	return 0;
}