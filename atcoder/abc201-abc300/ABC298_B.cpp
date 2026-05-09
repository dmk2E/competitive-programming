/*アルゴリズムと工夫点(Coloring Matrix/CPU: 2 ms  Memory: 4012 KB  Length: 768 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
using namespace std;

int n,a[MAX_N][MAX_N],b[MAX_N][MAX_N];

bool judge(){
	int i,j;
	rep(i,n)
		rep(j,n){
			if(a[i][j]==1&&b[i][j]==0)
				return false;
		}
	return true;
}

void rotate(){
	int i,j,temp[MAX_N][MAX_N];
	rep(i,n)
		rep(j,n)
			temp[i][j]=a[n-1-j][i];
	rep(i,n)
		rep(j,n)
			a[i][j]=temp[i][j];
}

void show(){
	int i,j;
	rep(i,n){
		rep(j,n)
			printf("%d ",a[i][j]);
		puts("");
	}
}

int main() {
	int i,j;
	scanf("%d",&n);
	rep(i,n)
		rep(j,n)
			scanf("%d",&a[i][j]);
	rep(i,n)
		rep(j,n)
			scanf("%d",&b[i][j]);
	rep(i,4){
		if(judge())
			break;
		rotate();
	}
	printf("%s\n",i==4?"No":"Yes");
	return 0;
}