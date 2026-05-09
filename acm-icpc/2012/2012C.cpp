/*アルゴリズムと工夫点(偏りのあるサイコロ/CPU: 0 ms Memory: 3800 KB  Length: 2853 B)
平面上の各マスについて,サイコロが重なっている個数をheight配列に保持しつつ,3方向の目の値を更新しながらのシミュレーションで解ける.
サイコロの移動は最大でも,0+1+2+...+n-1=n*(n-1)/2 であるから,最悪計算量はO(n^2)<10^3 より十分高速.
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define BELOW 6
#define FRONT 6
#define MAX_D 4
#define MAX_H 200
#define MAX_W 200
#define START 100
#define NIL -1
using namespace std;

//平面を上から見た時,right[下方向の目][正面に見えている目]=(右方向の目)
const int rright[BELOW][FRONT]={{-1,3,1,4,2,-1}
                               ,{2,-1,5,0,-1,3}
                               ,{4,0,-1,-1,5,1}
                               ,{1,5,-1,-1,0,4}
                               ,{3,-1,0,5,-1,2}
                               ,{-1,2,4,1,3,-1}};
int n,t,f,height[MAX_H+1][MAX_W+1],mmap[MAX_H+1][MAX_W+1],count[BELOW],dy[]={1,0,-1,0},dx[]={0,1,0,-1};

int nxt(int front,int below,int y,int x){
    int max=NIL,maxI=NIL;
    if(3<=below&&below<=5&&max<below&&height[y][x]>height[y+dy[0]][x+dx[0]]){
        max=below;
        maxI=0;
    }
    if(3<=rright[below][front]&&rright[below][front]<=5&&max<rright[below][front]&&height[y][x]>height[y+dy[1]][x+dx[1]]){
        max=rright[below][front];
        maxI=1;
    }
    if(3<=abs(5-below)&&abs(5-below)<=5&&max<abs(5-below)&&height[y][x]>height[y+dy[2]][x+dx[2]]){
        max=abs(5-below);
        maxI=2;
    }
    if(3<=abs(5-rright[below][front])&&abs(5-rright[below][front])<=5&&max<abs(5-rright[below][front])&&height[y][x]>height[y+dy[3]][x+dx[3]]){
        max=abs(5-rright[below][front]);
        maxI=3;
    }
    return maxI;
}

void update(int front,int below){
    int y=START,x=START,d;
    while((d=nxt(front,below,y,x))!=NIL){
        //printf("%d %d\n",y,x);printf("(%d,%d,%d)\n",front+1,below+1,rright[below][front]+1);
        y=y+dy[d];x=x+dx[d];
        switch(d){
            case 0:
                d=below;
                below=front;
                front=abs(5-d);
                break;
            case 1:
                front=abs(5-rright[below][front]);
                break;
            case 2:
                d=front;
                front=below;
                below=abs(5-d);
                break;
            default:
                front=rright[below][front];
                break;
        }
    }
    //printf("finished:%d %d\n",y,x);printf("finished(%d,%d,%d)\n",front+1,below+1,rright[below][front]+1);
    if(mmap[y][x]!=NIL)
        count[mmap[y][x]]--;
    mmap[y][x]=front;
    count[front]++;
    height[y][x]++;
}

int main(){
    int i,j;
    bool first;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        rep(i,MAX_H+1)rep(j,MAX_W+1){mmap[i][j]=NIL;height[i][j]=0;};
        rep(i,FRONT)count[i]=0;
        while(n--){
            scanf("%d%d",&t,&f);
            t--;f--;
            //printf("start\n");
            update(t,f);
        }
        rep(i,5)
            printf("%d ",count[i]);
        printf("%d\n",count[i]);
    }
    return 0;
}