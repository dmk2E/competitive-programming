/*アルゴリズムと工夫点(CP Classes/CPU: 139 ms  Memory: 4720 KB  Length: 605 B)
「要素の検索はソートして二分探索」は自力で思いつけた。絶対値が最小になるよるためには、絶対値の中身が負の値になる近辺を調べればよいため、この解法が活きる。
最悪計算量はO((N+Q)log2(N))<10^7 となり、高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n,q;

int main() {
	int i,left,right,mid;
	scanf("%d",&n);
	vector<int> a(n);
	rep(i,n)
		scanf("%d",&a[i]);
	sort(a.begin(),a.end());
	scanf("%d",&q);
	while(q--){
		scanf("%d",&i);
		left=0;right=n;
		while(left<right){
			mid=(left+right)/2;
			if(i-a[mid]>=0)
				left=mid+1;
			else
				right=mid;
		}
		mid=a[n-1]+i+1;   //当初a[n-1]+1としてしまっており、minの初期値が適切ではなかった。悔しい。
		if(left<n&&mid>abs(a[left]-i))
			mid=abs(a[left]-i);
		if(left-1>=0&&mid>abs(a[left-1]-i))
			mid=abs(a[left-1]-i);
		printf("%d\n",mid);
	}
	return 0;
}