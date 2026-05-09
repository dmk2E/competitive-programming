/*アルゴリズムと工夫点(Break Number/CPU: 1 ms  Memory: 3888 KB  Length: 453 B)
求める解Xは、X=2^x<=n を満たすxの値の中で最大となるxの値を用いて2^xと表されるものとなる。したがって、繰り返し二乗法のpower関数を用いた、指数xの値二分探索で解ける。
最悪計算量は、O(log2(log2(n))*log2(log2(n)))<10^2 となり十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;

int power(int x,int a){
	if(a==0)
		return 1;
	int temp=power(x*x,a/2);
	if(a%2==1)
		temp*=x;
	return temp;
}

int main() {
	int left,right,mid;
	scanf("%d",&n);
	left=1;right=10;
	while(left<right){
		mid=(left+right)/2;
		if(power(2,mid)<=n)
			left=mid+1;
		else
			right=mid;
	}
	printf("%d\n",power(2,left-1));
	return 0;
}