/*アルゴリズムと工夫点(怪文書/CPU: 9 ms  Memory: 3672 KB  Length: 664 B)
全ての文字列において共通する文字を、種類と数のペアでmapを用いて管理し、最後に辞書順で出力すればよい。計算量は、O(n^2*log2(n))<10^5 より十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_ALFA 26
#define MAX_S 50
using namespace std;

int n;
string s;
map<char,int> nowV,preV;

int main() {
	int i, size;
	cin >> n;
	getchar();
	getline(cin, s);
	for (i = 0, size = s.size(); i < size; i++)
		preV[s[i]]++;
	while (--n) {
		//printf("preV:%d nowV:%d\n",preV.size(),nowV.size());
		getline(cin, s);
		size = s.size();
		rep(i, size) {
			if (preV[s[i]] > 0) {
				nowV[s[i]]++;
				preV[s[i]]--;
			}
		}
		swap(preV,nowV);
		nowV.clear();
	}
	for (pair<char,int> p : preV) {
		rep(i, p.second)
			printf("%c",p.first);
	}
	puts("");
	return 0;
}