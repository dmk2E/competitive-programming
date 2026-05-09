/*アルゴリズムと工夫点(Colored Ball/CPU: 459 ms  Memory: 25888 KB  Length: 598 B)
setなどの特定のデータの入れ替えにおいては、標準ライブラリによって定義されているswap関数を用いた方が、代入を3回繰り返すことに依る値の入れ替えより圧倒的に高速になる。
*/
#include <bits/stdc++.h>
#define MAX_N 200000
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

int n, q,a,b;
set<int> box[MAX_N];

int main() {
	int i,j;
	set<int> temp;
	scanf("%d%d",&n,&q);
	rep(i, n) {
		scanf("%d",&j);
		box[i].insert(j);
	}
	while (q--) {
		scanf("%d%d",&a,&b);
		a--; b--;
		if (box[a].size() < box[b].size()) {
			for (int i: box[a])
				box[b].insert(i);
			box[a].clear();
		}
		else {
			for (int i : box[b])
				box[a].insert(i);
			box[b].clear();
			swap(box[a], box[b]);
		}
		printf("%d\n",(int)box[b].size());
	}
	return 0;
}