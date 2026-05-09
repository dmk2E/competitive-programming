/*アルゴリズムと工夫点(Cluttered Paper/CPU: 33 ms  Memory: 8108 KB  Length: 709 B)
mmap[i][j]:(i<=x<i+1,j<=y<j+1) の範囲に何枚紙が重なっているかを表す。これはimos法を用いることで、O(N+MAX_H*MAX_W)<10^7 の最悪計算量で実行可能。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
#define MAX_H 1000
#define MAX_W 1000
using namespace std;

int n,lx,ly,rx,ry,mmap[MAX_H+1][MAX_W+1]={0};

void paint(int ly,int lx,int ry,int rx){
	mmap[ly][lx]++;
	mmap[ly][rx+1]--;
	mmap[ry+1][lx]--;
	mmap[ry+1][rx+1]++;
}

int main() {
	int i,j,cnt[MAX_N+1]={0};
	scanf("%d",&n);
	rep(i,n){
		scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
		paint(ly,lx,ry-1,rx-1);
	}
	rep(i,MAX_H){
		rep(j,MAX_W)
			mmap[i][j+1]+=mmap[i][j];
	}
	rep(j,MAX_W){
		rep(i,MAX_H)
			mmap[i+1][j]+=mmap[i][j];
	}
	rep(i,MAX_H)
		rep(j,MAX_W)
			cnt[mmap[i][j]]++;
	rep(i,n)
		printf("%d\n",cnt[i+1]);
	return 0;
}