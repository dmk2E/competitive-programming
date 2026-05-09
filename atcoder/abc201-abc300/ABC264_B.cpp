/*アルゴリズムと工夫点(Nice Grid/CPU: 1 ms Memory: 3892 KB  Length: 1058 B)
マス(R,C)と(y,x)とのチェビシェフ距離 max(|R-y|,|C-x|) が奇数の時のみ黒色となるという解説の方が高速かつ実装量も少ない．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 15
#define MAX_W 15
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int r,c;
const int dy[]={0,1,0,-1},dx[]={1,0,-1,0},MAX_D=4,NIL=-1;

int main(){
    int i,j,k;
    scanf("%d%d",&r,&c);
    r--;c--;
    vector<vector<int> > vis(MAX_H,vector<int>(MAX_W,NIL));
    k=1;
    auto paint=[&](int y,int x,int c)->void{
        int now=0,yy,xx;
        vis[y][x]=c;
        while(now<MAX_D){
            yy=y+dy[now];xx=x+dx[now];
            if(0<=yy&&yy<MAX_H&&0<=xx&&xx<MAX_W&&vis[yy][xx]==NIL){
                vis[yy][xx]=c;
                y=yy;
                x=xx;
            }else
                now++;
        }
    };
    rep(i,MAX_H)rep(j,MAX_W){
        if(vis[i][j]==NIL){
            paint(i,j,k);
            k=(k+1)%2;
        }
    }
    // rep(i,MAX_H){
    //     rep(j,MAX_W)printf("%d",vis[i][j]);puts("");
    // }
    printf("%s\n",vis[r][c]?"black":"white");
    return 0;
}