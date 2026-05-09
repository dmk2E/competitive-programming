/*アルゴリズムと工夫点(Yokan Party/CPU: 18 ms  Memory: 4288 KB  Length: 669 B)
「最小値の最大化問題」や「最大値の最小化問題」では二分探索は有効であることが多いというのは分かっていたが、解法として思いつくことができなかった。解を予測してその値が条件を満たすかの判定結果により、探索
範囲を狭めることができる場合、二分探索を解法の候補として思考できるようにしたい(判定するアルゴリズムの計算量によっては不可能となる可能性に注意)。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
using namespace std;

int n,l,k,a[MAX_N];

bool judge(int m){
	int i=0,temp=0,sum=0,cnt=0;
	while(i<n){
		temp=0;
		while(temp<m&&i<n)
			temp+=a[i++];
		if(temp<m)
			break;
		cnt++;
		sum+=temp;
		if(cnt==k)
			return l-sum>=m;
	}
	return false;
}

int main() {
	int i,left,right,mid;
	scanf("%d%d%d",&n,&l,&k);
	left=0;
	rep(i,n){
		scanf("%d",&a[i]);
		a[i]-=left;
		left+=a[i];
	}
	left=0;
	right=l;
	while(left<right){
		mid=(left+right)/2;
		if(judge(mid))
			left=mid+1;
		else
			right=mid;
	}
	printf("%d\n",left-1);
	return 0;
}