/*アルゴリズムと工夫点(Decrease (Contestant ver.)/CPU: 1 ms  Memory: 3900 KB  Length: 601 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 50
#define MAX_A ((1e16)+1000)
using namespace std;

long long k,a[MAX_N];

bool judge(int n){
	int i,j;
	rep(i,n)
		a[i]=i+k/n;
	if(a[i-1]>MAX_A)
		return false;
	rep(i,k%n){
		a[i]+=n;
		rep(j,n){
			if(j!=i)
				a[j]--;
		}
		rep(j,n)
			if(a[j]>MAX_A||a[j]<0)
				return false;
	}
	return true;
}

int main() {
	int i,n;
	scanf("%lld",&k);
	for(n=2;n<=MAX_N;n++)
		if(judge(n))
			break;
	printf("%d\n",n);
	rep(i,n-1)
		printf("%lld ",a[i]);
	printf("%lld\n",a[i]);
	return 0;
}