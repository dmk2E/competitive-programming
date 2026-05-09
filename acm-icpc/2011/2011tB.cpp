/*アルゴリズムと工夫点(ブレイブ・フォース・ストーリー/CPU: 0 ms Memory: 3616 KB  Length: 1483 B)
進める方向が6方向あることと、障害物に注意して指定ターン数だけ幅優先探索を行う。ただし負の座標が存在するため、ある定数だけ座標を平行移動する必要がある。与えられる座標の絶対値の最大値は30であり、
最大ターン数は30であるから、原点を(60,60)となるように調整した。
最悪計算量は、O(MAX_X*MAX_Y)<10^5 となり十分高速。
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_Y 120
#define MAX_X 120
#define MAX_D 6
#define NIL -1
using namespace std;

typedef pair<int,int> p;

int t,n,dy[]={-1,-1,0,1,1,0},dx[]={0,-1,1,0,1,-1};
bool mmap[MAX_Y+1][MAX_X+1];

int bfs(int y,int x){
    int i,j,cnt=0,visited[MAX_Y+1][MAX_X+1];
    p now;
    queue<p> que;
    rep(i,MAX_Y+1)
        rep(j,MAX_X+1)
            visited[i][j]=NIL;
    visited[y][x]=0;
    cnt++;
    que.push(p(y,x));
    while(que.size()){
        now=que.front();que.pop();
        if(visited[now.first][now.second]>=t)
            continue;
        rep(i,MAX_D){
            y=now.first+dy[i];x=now.second+dx[i];
            if(y>=0&&y<MAX_Y+1&&x>=0&&x<MAX_X+1&&mmap[y][x]&&visited[y][x]==NIL){
                que.push(p(y,x));
                visited[y][x]=visited[now.first][now.second]+1;
                cnt++;
            }
        }
    }
    //rep(i,MAX_Y+1){rep(j,MAX_X+1)printf("%3d",mmap[i][j]?(visited[i][j]==NIL?0:visited[i][j]):-1);puts("");}
    return cnt;
}

int main(){
    int i,j;
    while(1){
        scanf("%d%d",&t,&n);
        if(!(t||n))
            break;
        rep(i,MAX_Y+1)
            rep(j,MAX_X+1)
                mmap[i][j]=true;
        while(n--){
            scanf("%d%d",&i,&j);
            i+=MAX_Y/2;
            j+=MAX_X/2;
            mmap[j][i]=false;
        }
        scanf("%d%d",&i,&j);
        printf("%d\n",bfs(j+MAX_Y/2,i+MAX_X/2));
    }
    return 0;
}