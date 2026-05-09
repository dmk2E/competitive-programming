/*アルゴリズムと工夫点(Score Sum Queries/CPU: 29 ms  Memory: 4580 KB  Length: 483 B)
「区間の合計値」は累積和を用いることで高速に求めることができる。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_C 2
#define MAX_N 100000
using namespace std;

int n,c,sumP[MAX_C][MAX_N+1];

int main() {
	int i,j;
	sumP[0][0]=sumP[1][0]=0;
	scanf("%d",&n);
	rep(i,n){
		scanf("%d%d",&c,&j);
		sumP[c-1][i+1]=sumP[c-1][i]+j;
		sumP[c%2][i+1]=sumP[c%2][i];
	}
	scanf("%d",&c);
	while(c--){
		scanf("%d%d",&i,&j);
		printf("%d %d\n",sumP[0][j]-sumP[0][i-1],sumP[1][j]-sumP[1][i-1]);
	}
	return 0;
}