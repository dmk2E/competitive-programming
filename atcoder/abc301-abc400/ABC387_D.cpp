/*アルゴリズムと工夫点(Snaky Walk/CPU: 51 ms Memory: 15460 KB  Length: 2765 B)
マスそれぞれについて，そのマスに到達した時の移動の仕方が{縦移動，横移動}の2通り存在するため，H*W*2個の頂点を持つ有向グラフ上での幅優先探索で解く．
最悪計算量は O(2*H*W*2)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int y,x;
    bool state;

    Data(int yy=0,int xx=0,int sstate=false):y(yy),x(xx),state(sstate){}
};


int h,w;

int main(){
    int i,j,sy,sx,gy,gx;
    scanf("%d%d",&h,&w);
    vector<vector<bool> > mmap(h,vector<bool>(w,false));
    rep(i,h){
        getchar();
        rep(j,w){
            switch(getchar()){
                case 'S':
                    sy=i;
                    sx=j;
                    mmap[i][j]=true;
                    break;
                case 'G':
                    gy=i;
                    gx=j;
                    mmap[i][j]=true;
                    break;
                case '#':
                    mmap[i][j]=false;
                    break;
                default:
                    mmap[i][j]=true;
            }
        }
    }
    //printf("sy:%d sx:%d\n",sy,sx);
    const int INF=(int)(1e9),dy[]={-1,1,0,0},dx[]={0,0,1,-1},MAX_D=4;
    auto bfs=[&](int sy,int sx,int gy,int gx)->int{
        int i,j,y,x;
        vector<vector<vector<int>>> vis(2,vector<vector<int> >(h,vector<int>(w,INF)));
        queue<Data> que;
        Data now;
        vis[0][sy][sx]=0;
        vis[1][sy][sx]=0;
        rep(i,MAX_D){
            y=sy+dy[i];
            x=sx+dx[i];
            if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]&&vis[i<(MAX_D/2)][y][x]==INF){
                vis[i<(MAX_D/2)][y][x]=1;
                que.push(Data(y,x,i<(MAX_D/2)));
            }
        }
        while(que.size()){
            now=que.front();que.pop();
            //printf("%d %d\n",now.y,now.x);
            if(now.state){
                for(i=2;i<MAX_D;i++){
                    y=now.y+dy[i];
                    x=now.x+dx[i];
                    if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]&&vis[i<(MAX_D/2)][y][x]==INF){
                        vis[i<(MAX_D/2)][y][x]=vis[now.state][now.y][now.x]+1;
                        que.push(Data(y,x,i<(MAX_D/2)));
                    }
                }
            }else{
                for(i=0;i<(MAX_D/2);i++){
                    y=now.y+dy[i];
                    x=now.x+dx[i];
                    if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]&&vis[i<(MAX_D/2)][y][x]==INF){
                        vis[i<(MAX_D/2)][y][x]=vis[now.state][now.y][now.x]+1;
                        que.push(Data(y,x,i<(MAX_D/2)));
                    }
                }
            }
        }
        return (vis[0][gy][gx]==INF&&vis[1][gy][gx]==INF)?-1:min(vis[0][gy][gx],vis[1][gy][gx]);
    };
    printf("%d\n",bfs(sy,sx,gy,gx));
    return 0;
}