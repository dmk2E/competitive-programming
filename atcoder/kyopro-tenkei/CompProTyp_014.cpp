/*アルゴリズムと工夫点(We Used to Sing a Song Together/CPU: 33 ms  Memory: 4164 KB  Length: 399 B)
「ソートして貪欲法」:昇順ソートしてわかりやすくすることはできていたが、貪欲法で解けるとは気づけなかった。図を描く中で気づけるようになりたい。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;
vector<int> a,b;

int main() {
	int i;
	long long sum=0;
	scanf("%d",&n);
	a.resize(n);b.resize(n);
	rep(i,n)
		scanf("%d",&a[i]);
	rep(i,n)
		scanf("%d",&b[i]);
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	rep(i,n)
		sum+=abs(a[i]-b[i]);
	printf("%lld\n",sum);
	return 0;
}