/*アルゴリズムと工夫点(等しい合計点/CPU: 0 ms  Memory: 3456 KB  Length: 793 B)
太郎と花子が持つカードの枚数をその点数毎に保持する配列taroとhanakoを用意する。この作成はO(n+m)で可能。カードを入れ替えても合計点が同じということは、交換前の太郎と花子がもつカードの合計点をそれぞれsumT,sumHとし、交換する
カードの数をそれぞれi,jとすると、sumT-i+j=sumH+i-j ∴2*j=sumH-sumT+2*i となるから、iが定まれば、jも一意に定まるため、そんなjが存在するか、iについて調べればよい。
最悪計算量は、O(n+m+n)=O(n+m)<10^3 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_P 100
using namespace std;

int n, m, taro[MAX_P + 1], hanako[MAX_P + 1];

int main() {
	int sumT, sumH, i, minT, minH;
	while (1) {
		scanf("%d%d",&n,&m);
		if (!(n || m))
			break;
		rep(i, MAX_P + 1)
			taro[i] = hanako[i] = 0;
		sumT = sumH = 0;
		while (n--) {
			scanf("%d", &i);
			taro[i]++;
			sumT += i;
		}
		while (m--) {
			scanf("%d", &i);
			hanako[i]++;
			sumH += i;
		}
		minT = minH = MAX_P + 1;
		rep(i, MAX_P + 1)
			if (taro[i] > 0 && (n = sumH - sumT + 2 * i) % 2 == 0 && 0 <= n / 2 && n / 2 <= MAX_P && hanako[n / 2] > 0 && i + n / 2 < minT + minH) {
				minT = i;
				minH = n / 2;
			}
		if (minT == MAX_P + 1)
			printf("%d\n", -1);
		else
			printf("%d %d\n", minT, minH);
	}
	return 0;
}