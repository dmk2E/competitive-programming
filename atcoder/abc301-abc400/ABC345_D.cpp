/*アルゴリズムと工夫点(Tiling/CPU: 173 ms  Memory: 3852 KB  Length: 2031 B)
敷き詰めなければならないから、おくタイルの左側と左上は既にタイルがおかれているか、範囲外になっているように置いていくことを考えればよい。
全探索の仕方によってかかる計算量に違いが生じてしまうため、余程強力な枝刈り条件が見つかってない場合、全探索による計算量は約10^8以下になるようにすること。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 7
#define MAX_H 10
#define MAX_W 10
using namespace std;

typedef struct tyoho{
	int a,b;
}Tyoho;

int n,h,w;
Tyoho ddata[MAX_N];

typedef struct data{
	int num,rest,mmap[MAX_H][MAX_W];
	data(){}
	data(int nnum,int rrest,int mmmap[MAX_H][MAX_W]):num(nnum),rest(rrest){
		int i,j;
		rep(i,h)
			rep(j,w)
				mmap[i][j]=mmmap[i][j];
	}
}Data;

bool judge(int num,int sy,int sx,int a,int b,int mmap[MAX_H][MAX_W]){
	int i,j;
	rep(i,a)
		rep(j,b){
			if(mmap[sy+i][sx+j]>0){
				return false;
			}
			mmap[sy+i][sx+j]=num+1;
		}
	return true;
}

void showMap(int mmap[][MAX_W]){
	int i,j;
	rep(i,h){
		rep(j,w)
			printf("%d",mmap[i][j]);
		puts("");
	}
}

bool dfs(Data now,bool flag[]){
	/*
	printf("%d:\n",now.num);
	showMap(now.mmap);
	puts("");
	*/
	if(now.num==n)
		return now.rest==0;
	int i,j,k;
	Data temp=now;
	rep(k,n){
		if(flag[k]==false){
			flag[k]=true;
			//printf("num:%d\n",k);
			rep(i,h){
				rep(j,w){
					if(now.mmap[i][j]==0&&(i-1<0||now.mmap[i-1][j]>0)&&(j-1<0||now.mmap[i][j-1]>0)){
						temp=now;
						if(i+ddata[k].a-1<h&&j+ddata[k].b-1<w&&judge(k,i,j,ddata[k].a,ddata[k].b,temp.mmap)){
							temp.num++;
							temp.rest-=ddata[k].a*ddata[k].b;
							if(dfs(temp,flag))
								return true;
						}
						temp=now;
						if(i+ddata[k].b-1<h&&j+ddata[k].a-1<w&&judge(k,i,j,ddata[k].b,ddata[k].a,temp.mmap)){
							temp.num++;
							temp.rest-=ddata[k].a*ddata[k].b;
							if(dfs(temp,flag))
								return true;
						}
						temp=now;
						temp.num++;
						if(dfs(temp,flag))
							return true;
						break;
					}
				}
				if(j<w)
					break;
			}
			flag[k]=false;
		}
	}
	return false;
}

int main() {
	int i,j,k,mmap[MAX_H][MAX_W]={0};
	bool flag[MAX_N]={0};
	scanf("%d%d%d",&n,&h,&w);
	rep(i,n){
		scanf("%d%d",&ddata[i].a,&ddata[i].b);
	}
	printf("%s\n",dfs(Data(0,h*w,mmap),flag)?"Yes":"No");
	return 0;
}