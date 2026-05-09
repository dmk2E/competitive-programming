/*アルゴリズムと工夫点(ログイン/ログアウト記録の解析/CPU: 40 ms  Memory: 30588 KB  Length: 865 B)
時間の幅は720しかないので、生徒毎にその時間に使用しているコンピュータの個数を保持させた配列llogを作成し、使用した時間は指定された時間内のllogにおける値が1以上となる要素の数から求めることができる。
llog[i][j]:生徒iが時間540+j に使っているコンピュータの個数。<-imos法で高速に作成可能。
最悪計算量は、O(2*MAX_R*M+r+q*MAX_R)=O(MAX_R*(M+q)+r)<10^6 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_M 10000
#define MIN_T 540
#define MAX_R 720
using namespace std;

int n, m, llog[MAX_M][MAX_R + 1], r, t, mm, s;

int main() {
	int i, j;
	while (1) {
		scanf("%d%d",&n,&m);
		if (!(n || m))
			break;
		rep(i, m)
			rep(j, MAX_R + 1)
				llog[i][j] = 0;
		scanf("%d",&r);
		while (r--) {
			scanf("%d%d%d%d",&t,&n,&mm,&s);
			if (s == 1)
				llog[mm - 1][t - MIN_T]++;
			else if (t  - MIN_T <= MAX_R)
				llog[mm - 1][t  - MIN_T]--;
		}
		rep(i, m)
			rep(j, MAX_R)
				llog[i][j + 1] += llog[i][j];
		scanf("%d", &n);
		while (n--) {
			scanf("%d%d%d",&t,&s,&mm);
			for (j = t-MIN_T,i=0; j <= s-MIN_T; j++) {
				if (llog[mm - 1][j] > 0)
					i++;
				//printf("%d ",llog[mm-1][j]);
			}
			//puts("");
			if (llog[mm - 1][j - 1] > 0)
				i--;
			printf("%d\n", i);
		}
	}
	return 0;
}