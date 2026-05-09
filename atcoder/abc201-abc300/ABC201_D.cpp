/*アルゴリズムと工夫点(Game in Momotetsu World/CPU: 94 ms Memory: 24256 KB  Length: 1373 B)
ミニマックス法という、特殊DPで解く問題。
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 2000
#define MAX_W 2000
#define INF 1000000000
using namespace std;

int h,w,memo[MAX_H][MAX_W];
bool visited[MAX_H][MAX_W]={0};
vector<vector<bool> > mmap;

int dp(int y,int x){
    if(visited[y][x]) return memo[y][x];
    visited[y][x]=true;
    if(y==h-1&&x==w-1) return memo[y][x]=0;
    if((y+x)%2==0){
        memo[y][x]=-INF;
        if(y+1<h) memo[y][x]=max(memo[y][x],dp(y+1,x)+(mmap[y+1][x]?1:-1));
        if(x+1<w) memo[y][x]=max(memo[y][x],dp(y,x+1)+(mmap[y][x+1]?1:-1));
    }else{
        memo[y][x]=INF;
        if(y+1<h) memo[y][x]=min(memo[y][x],dp(y+1,x)-(mmap[y+1][x]?1:-1));
        if(x+1<w) memo[y][x]=min(memo[y][x],dp(y,x+1)-(mmap[y][x+1]?1:-1));
    }
    return memo[y][x];
}

void showDP(){
    int i,j;
    rep(i,h){
        rep(j,w)
            printf("%d ",memo[i][j]);
        puts("");
    }
}

int main(){
    int i,j;
    char c;
    scanf("%d%d",&h,&w);
    mmap.resize(h,vector<bool>(w));
    rep(i,h){
        getchar();
        rep(j,w){
            c=getchar();
            mmap[i][j]=c=='+';
        }
    }
    i=dp(0,0);
    //showDP();
    if(i==0)
        puts("Draw");
    else if(i>0)
        puts("Takahashi");
    else
        puts("Aoki");
    return 0;
}

/*O(2^(h+w))のアルゴリズム
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define WIN 1
#define LOSE -1
#define DRAW 0
using namespace std;

int h,w,cnt=0;

int dfs(int y,int x,int t,int a,bool turn,vector<vector<bool> >& mmap){
    if(y==h-1&&x==w-1)
        return t==a?DRAW:t>a?WIN:LOSE;
    int down=WIN,right=WIN;
    cnt+=2;
    if(turn){//高橋のターン
        if(y+1<h)
            down=dfs(y+1,x,t+(mmap[y+1][x]?1:-1),a,!turn,mmap);
        if(x+1<w)
            right=dfs(y,x+1,t+(mmap[y][x+1]?1:-1),a,!turn,mmap);
        //printf("Takahashi(%d,%d)down:%d right:%d\n",y,x,down,right);
        if(y+1>=h)
            return right==WIN?WIN:right==DRAW?DRAW:LOSE;
        if(x+1>=w)
            return down==WIN?WIN:down==DRAW?DRAW:LOSE;
        return (right==WIN||down==WIN)?WIN:(right==DRAW||down==DRAW)?DRAW:LOSE;
    }
    //青木のターン
    if(y+1<h)
        down=dfs(y+1,x,t,a+(mmap[y+1][x]?1:-1),!turn,mmap);
    if(x+1<w)
        right=dfs(y,x+1,t,a+(mmap[y][x+1]?1:-1),!turn,mmap);
    //printf("Aoki(%d,%d)down:%d right:%d\n",y,x,down,right);
    return (right==WIN&&down==WIN)?WIN:(right==LOSE||down==LOSE)?LOSE:DRAW;
}

int main(){
    int i,j;
    char c;
    scanf("%d%d",&h,&w);
    vector<vector<bool> > mmap(h,vector<bool>(w));
    rep(i,h){
        getchar();
        rep(j,w){
            c=getchar();
            mmap[i][j]=c=='+';
        }
    }
    //return 0;
    switch(dfs(0,0,0,0,true,mmap)){
        case WIN:
            puts("Takahashi");
            break;
        case LOSE:
            puts("Aoki");
            break;
        default:
            puts("Draw");
    }
    return 0;
}
*/