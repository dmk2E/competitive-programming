/*アルゴリズムと工夫点(Minimum Coins/CPU: 288 ms  Memory: 3908 KB  Length: 492 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_C 10000
using namespace std;

int n,a,b,c;

int main() {
	int i,j,min=MAX_C;
	long long sum=0;
	scanf("%d%d%d%d",&n,&a,&b,&c);
	rep(i,MAX_C){
		if((sum=(long long)n-(long long)a*i)<0)
			break;
		rep(j,MAX_C){
			if((sum-(long long)b*j)<0)
				break;
			sum-=(long long)b*j;
			if(sum%c==0&&i+j+sum/c<min)
				min=i+j+sum/c;
			sum+=(long long)b*j;
		}
	}
	printf("%d\n",min);
	return 0;
}