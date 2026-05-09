/*アルゴリズムと工夫点(Restrictive Filesystem/CPU: 260 ms  Memory: 3888 KB  Length: 1502 B)
メモリの状態を、(セクタ番号の先頭:s,セクタ番号の最後尾+1:e,書き込まれているファイルの識別子l)の状態で、sの昇順となるように、リスト構造で保持する。こうすることで、[s,e)のメモリ上にどのファイルが書き込まれているかを保持でき、その一つ
一つのデータの個数はN個以下になる。よって参照の際、線形的にリストを辿って行けばいいから、その最悪計算量はO(N)となる。消去する際は、ファイルのサイズ分消去しきるまで先頭のメモリから消していく。これも線形的に辿っていけばよい。
書き込む際は、内容が空の部分の範囲がファイルのサイズより大きい場合、ファイルを書き込んだ部分と内容が空のままの部分とで二つに分ける必要があり、その時の計算量はO(1)となる。ファイルのサイズより小さい場合、空の部分全てをファイルに埋め
ればよいため、lの書き換えるだけで良く、線形的にリストを辿って書き込んでいけばよい。
全体の最悪計算量はO(N^2)=10^8(簡潔な処理なら間に合う) となるが、命令によってはリストのデータの数はNより小さくなり、最悪計算量は10^8未満になるため、間に合うと予測できた。
*リスト構造において、一度でも要素を追加したり消去したりした場合、イテレータをbegin関数等でもう一度取得し直さなければならないことに注意。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_NUM 1000000000
#define NIL -1
using namespace std;

typedef struct data {
	int s, e, l;

	data(int ss=0, int ee=0, int ll=0):s(ss),e(ee),l(ll) {}
}Data;

int n, l, s;
char command;
list<Data> llog;
map<int, int> ssize;

int main() {
	int i;
	list<Data>::iterator it;
	while (1) {
		scanf("%d",&n);
		if (!n)
			break;
		llog.push_back(Data(0, MAX_NUM + 1, NIL));
		//ssize[NIL] = MAX_NUM;
		while (n--) {
			getchar();
			scanf("%c", &command);
			switch (command) {
				case 'W':
					scanf("%d%d", &l, &s);
					//ssize[NIL] -= s;
					ssize[l] = s;
					for (it = llog.begin(); it != llog.end(); it++) {   //最悪計算量O(N)
						if ((*it).l == NIL) {
							if ((*it).s + s < (*it).e) {
								(*it).s += s;
								llog.insert(it, Data((*it).s - s, (*it).s, l));
								break;
							}
							else {
								(*it).l = l;
								s -= (*it).e - (*it).s;
								if (s == 0)
									break;
							}
						}
					}
					break;
				case 'R':
					scanf("%d", &l);
					for (it = llog.begin(); it != llog.end(); it++) {   //最悪計算量O(N)
						if ((*it).s <= l && l < (*it).e)
							break;
					}
					printf("%d\n", (*it).l);
					break;
				default :
					scanf("%d", &l);
					//ssize[NIL] += ssize[l];
					for (it = llog.begin(); it != llog.end() && ssize[l] > 0; it++) {   //最悪計算量O(N)
						if ((*it).l == l) {
							ssize[l] -= (*it).e - (*it).s;
							(*it).l = NIL;
						}
					}
					break;
			}
		}
		llog.clear();
		ssize.clear();
		puts("");
	}
	return 0;
}