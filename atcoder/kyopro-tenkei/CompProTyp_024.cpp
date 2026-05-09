/*アルゴリズムと工夫点(Select +／- One/CPU: 1 ms  Memory: 3800 KB  Length: 356 B)

*/
#include<iostream>
#include<cstdlib>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1000
using namespace std;

int n,k,a[MAX_N];

int main() {
	int i,j,sum=0;
	scanf("%d%d",&n,&k);
	rep(i,n)
		scanf("%d",&a[i]);
	rep(i,n){
		scanf("%d",&j);
		sum+=abs(j-a[i]);
	}
	printf("%s\n",(sum<=k&&((k-sum)%2==0))?"Yes":"No");
	return 0;
}