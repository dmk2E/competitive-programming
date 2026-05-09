/*アルゴリズムと工夫点(スクウェア・ルート/CPU: 1760 ms  Memory: 21388 KB  Length: 659 B)
正方形の縦の長さのパターン数は、n+(n-1)+(n-2)+...+1=(n^2+n)/2 横の長さも同様に (m^2+m)/2 となる。縦の長さを固定して、横の長さを固定する流れを一つの繰り返し構造で書こうとすると、O(n^2*m^2)>10^12>10^8 となり間に合わない。
しかし、縦と横それぞれの長さの全パターン数の列挙はそれぞれO(n^2),O(m^2)≒10^6 となり十分高速。従って、まず縦の長さを全列挙し、(長さ,その個数)でハッシュ法で保持。その後、横の長さの全列挙を行い、列挙した長さそれぞれと同じ長
さの縦の辺の数を足していくことで、求める数を出せる。最悪計算量は、O(n^2+m^2)≒10^6<10^7 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1500
#define MAX_M 1500
using namespace std;

int n, m, sumN[MAX_N + 1], sumM[MAX_M + 1];   //与えられるh,wの値は累積和で保持し、長さのパターン数列挙を簡略化。

int main() {
	int i, j, cnt;
	map<int, int> v;
	while (1) {
		scanf("%d%d", &n, &m);
		if (!(n || m))
			break;
		sumN[0] = 0;
		rep(i, n) {
			scanf("%d", &j);
			sumN[i + 1] = sumN[i] + j;
		}
		sumM[0] = 0;
		rep(i, m) {
			scanf("%d", &j);
			sumM[i + 1] = sumM[i] + j;
		}
		rep(i, n)
			for (j = i + 1; j <= n; j++)
				v[sumN[j] - sumN[i]]++;
		cnt = 0;
		rep(i, m)
			for (j = i + 1; j <= m; j++)
				cnt += v[sumM[j] - sumM[i]];
		printf("%d\n", cnt);
		v.clear();
	}
	return 0;
}