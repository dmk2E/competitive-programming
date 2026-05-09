/*アルゴリズムと工夫点(/CPU:  ms  Memory:  KB  Length:  B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 200000
#define NIL -1
using namespace std;

int n,t,c[MAX_N],r[MAX_N];

int main() {
	int i,maxI;
	scanf("%d%d",&n,&t);
	rep(i,n)
		scanf("%d",&c[i]);
	rep(i,n)
		scanf("%d",&r[i]);
	maxI=NIL;
	rep(i,n){
		if(c[i]==t&&(maxI==NIL||r[maxI]<r[i]))
			maxI=i;
	}
	if(maxI==NIL){
		rep(i,n){
			if(c[i]==c[0]&&(maxI==NIL||r[maxI]<r[i]))
				maxI=i;
		}
	}
	printf("%d\n",maxI+1);
	return 0;
}