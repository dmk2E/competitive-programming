/*アルゴリズムと工夫点(Cross Sum/CPU: 460 ms  Memory: 44224 KB  Length: 496 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 2000
#define MAX_W 2000
using namespace std;

int h,w,a[MAX_H][MAX_W],sumRow[MAX_H]={0},sumColumn[MAX_W]={0};

int main() {
	int i,j;
	scanf("%d%d",&h,&w);
	rep(i,h)
		rep(j,w){
			scanf("%d",&a[i][j]);
			sumRow[i]+=a[i][j];
			sumColumn[j]+=a[i][j];
		}
	rep(i,h){
		rep(j,w-1)
			printf("%d ",sumRow[i]+sumColumn[j]-a[i][j]);
		printf("%d\n",sumRow[i]+sumColumn[j]-a[i][j]);
	}
	return 0;
}