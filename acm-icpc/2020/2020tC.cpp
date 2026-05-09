/*アルゴリズムと工夫点(忍ぶべし/CPU: 40 ms Memory: 15408 KB  Length: 2899 B)
座標を反転させることで,左上から右上に向かうようにしておくと,動的計画法で解ける.
*/
#include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define MAX_H 1000
#define MAX_W 1000
using namespace std;

typedef struct pair<int,int> p;

typedef struct data{
    int y,x,r;

    data(int yy=0,int xx=0,int rr=0):y(yy),x(xx),r(rr){}
}Data;

int n,sx,sy,gx,gy,x,y,r,lleft[MAX_H+1][MAX_W+1],up[MAX_H+1][MAX_W+1],dp[MAX_H+1][MAX_W+1];

int main(){
    int i,j,cnt,yy,xx;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        scanf("%d%d%d%d",&sx,&sy,&gx,&gy);
        sx--;sy--;gx--;gy--;
        vector<Data> sencer;cnt=0;
        vector<p> tmp;
        while(n--){
            scanf("%d%d%d",&x,&y,&r);
            x--;y--;
            if((x-r<=sx&&sx<=x+r)&&(y-r<=sy&&sy<=y+r))
                cnt++;
            else
                sencer.push_back(Data(y,x,r));
        }
        gy-=sy;
        gx-=sx;
        rep(i,sencer.size()){
            sencer[i].y-=sy;
            sencer[i].x-=sx;
        }
        sy=sx=0;
        i=gy-sy;j=gx-sx;
        if(i>=0){
            if(j<0){//左下ベクトル
                rep(i,sencer.size()){
                    sencer[i].x*=-1;
                }
                gx*=-1;
            }
        }else{
            if(j>=0){//右上ベクトル
                rep(i,sencer.size()){
                    sencer[i].y*=-1;
                }
                gy*=-1;
            }else{//左上ベクトル
                rep(i,sencer.size()){
                    sencer[i].y*=-1;
                    sencer[i].x*=-1;
                }
                gy*=-1;gx*=-1;
            }
        }
        rep(i,gy+1)rep(j,gx+1){lleft[i][j]=up[i][j]=0;}
        rep(i,sencer.size()){
            yy=max(0,sencer[i].y-sencer[i].r);xx=max(0,sencer[i].x-sencer[i].r);
            if(sencer[i].x+sencer[i].r-xx>=0){
                up[yy][xx]++;
                if(sencer[i].x+sencer[i].r+1<=gx+1)
                    up[yy][sencer[i].x+sencer[i].r+1]--;
            }
            if(sencer[i].y+sencer[i].r-yy>=0){
                lleft[yy][xx]++;
                if(sencer[i].y+sencer[i].r+1<=gy+1)
                    lleft[sencer[i].y+sencer[i].r+1][xx]--;
            }
        }
        rep(i,gy+1)rep(j,gx+1)up[i][j+1]+=up[i][j];
        rep(j,gx+1)rep(i,gy+1)lleft[i+1][j]+=lleft[i][j];
        //rep(i,gy+1){rep(j,gx+1)printf("%d",max(lleft[i][j],up[i][j]));puts("");}
        //rep(i,gy+1){rep(j,gx+1)printf("%d",lleft[i][j]);puts("");}puts("up");rep(i,gy+1){rep(j,gx+1)printf("%d",up[i][j]);puts("");}puts("----------------------------------");
        dp[0][0]=cnt;
        rep(j,gx)
            dp[0][j+1]=dp[0][j]+lleft[0][j+1];
        rep(i,gy)
            rep(j,gx+1){
                dp[i+1][j]=dp[i][j]+up[i+1][j];
                if(j-1>=0&&dp[i+1][j]>dp[i+1][j-1]+lleft[i+1][j])
                    dp[i+1][j]=dp[i+1][j-1]+lleft[i+1][j];
            }
        printf("%d\n",dp[gy][gx]);
    }
    return 0;
}