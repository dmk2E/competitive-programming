/*アルゴリズムと工夫点(大崎/CPU: 30 ms  Memory: 3896 KB  Length: 735 B)
発時刻dと着時刻aは共に 00:00:00 からの経過秒数に変換して扱う。時間 [d,a) の間に列車が1台必要になるから、00:00:00から23:59:59 の間で必要な列車の数の最大値を求めればよい。
一次元配列trainを用いて、imos法により全時間帯に置ける列車の数を求めることができるから、最悪計算量は O(n+MAX_TIME)<10^5 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_TIME 86400   //24*60*60
using namespace std;

int n, train[MAX_TIME];   //train[i]:i<=t<i+1 を満たすt秒間に使われている列車の数を表す。

int toSecond(string s) {
	int h=(s[0]-(int)'0')*10+s[1]-(int)'0', m= (s[3] - (int)'0') * 10 + s[4] - (int)'0', ss= (s[6] - (int)'0') * 10 + s[7] - (int)'0';
	return h * 60 * 60 + m * 60 + ss;
}

int main() {
	int i, j;
	string str;
	while (1) {
		scanf("%d",&n);
		if (!n)
			break;
		rep(i, MAX_TIME)
			train[i] = 0;
		while (n--) {
			cin >> str;
			i = toSecond(str);
			cin >> str;
			j = toSecond(str);
			train[i]++;
			train[j]--;
		}
		j = 0;
		rep(i, MAX_TIME - 1) {
			train[i + 1] += train[i];
			if (train[i + 1] > train[j])
				j = i + 1;
		}
		printf("%d\n", train[j]);
	}
	return 0;
}