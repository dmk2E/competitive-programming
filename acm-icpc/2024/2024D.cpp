/*アルゴリズムと工夫点(だんごむしではないむし/CPU: 10 ms Memory: 3704 KB  Length: 3287 B)
拡張BFS的なシミュレーションで解く．
障害物の座標が小さいため，その最大y座標MAX_Y，最大x座標MAX_Xとし，(MAX_Y+1)*(MAX_X+1)の二次元平面を考える．
この平面上で虫の移動を，距離dだけ移動し終わるまでシミュレーションする．
ただし，以下の場合は例外処理を行う．
・二次元平面の範囲外に出た場合，方向変換は行われないので，解を出力する
・あるマスに同じ向きから再度訪問する場合，そのマスを始点&終点とするループに入る．ループする分だけ進んだ後は，愚直にシミュレーションする（シミュレーションにより進む距離はMAX_Y*MAX_X以下であるため，問題ない）．
最悪計算量は，O(n+MAX_Y*MAX_X*4)<10^5 となり十分高速．
※問題URL：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1675&lang=ja
*/
//#include<iostream>
//#include<cassert>
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
#define MAX_XY 100
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Point{
    int y,x,dir;

    Point(int yy=0,int xx=0,int ddir=0):y(yy),x(xx),dir(ddir){}
};

int n,a,b;
ll d;

int main(){
    int i,j,k;
    const int NIL=-1,WALL=-2;
    const int dy[]={-1,0,1,0},MAX_D=4;
    const int dx[]={0,1,0,-1};
    while(1){
        scanf("%d",&n);
        if(!n)break;
        scanf("%d%d%lld",&a,&b,&d);
        vector<vector<vector<int> > > dist(MAX_D,vector<vector<int> >(MAX_XY+1,vector<int>(MAX_XY+1,NIL)));
        while(n--){
            scanf("%d%d",&i,&j);
            rep(k,MAX_D)dist[k][j][i]=WALL;
        }

        auto bfs=[&](int y,int x){
            queue<Point> que;
            Point now(y,x,1);
            que.push(now);
            dist[now.dir][now.y][now.x]=0;
            while(que.size()){
                now=que.front();que.pop();
                if(dist[now.dir][y][x]==d){// ループせず終了する場合
                    //printf("1:");
                    printf("%d %d\n",now.x,now.y);
                    return ;
                }
                //printf("(y,x)=(%d,%d) %d\n",now.y,now.x,dist[now.dir][now.y][now.x]);
                y=now.y+dy[now.dir];
                x=now.x+dx[now.dir];
                if(0<=y&&y<=MAX_XY&&0<=x&&x<=MAX_XY){
                    if(dist[now.dir][y][x]==NIL){
                        // 行き先が未訪問のマス
                        dist[now.dir][y][x]=dist[now.dir][now.y][now.x]+1;
                        que.push(Point(y,x,now.dir));
                    }else if(dist[now.dir][y][x]==WALL){
                        // 行き先が障害物の場合
                        dist[(now.dir+1)%MAX_D][now.y][now.x]=dist[now.dir][now.y][now.x];
                        que.push(Point(now.y,now.x,(now.dir+1)%MAX_D));
                    }else{
                        // 未訪問ではなかった場合
                        int loop_dist=dist[now.dir][now.y][now.x]+1-dist[now.dir][y][x];
                        d-=dist[now.dir][now.y][now.x]+1;
                        d%=loop_dist;
                        now=Point(y,x,now.dir);
                        break;
                    }
                }else{
                    // 範囲外に出た場合
                    ll rest=d-dist[now.dir][now.y][now.x];
                    //printf("2:");
                    printf("%lld %lld\n",now.x+(ll)dx[now.dir]*rest,now.y+(ll)dy[now.dir]*rest);
                    return ;
                }
            }
            //printf("d:%lld\n",d);
            // 残りの移動量だけシミュレーション
            while(d--){
                //printf("(y,x)=(%d,%d) d=%lld\n",now.y,now.x,d);
                y=now.y+dy[now.dir];
                x=now.x+dx[now.dir];
                while(dist[now.dir][y][x]==WALL){
                    // 行き先が障害物の場合
                    now.dir=(now.dir+1)%MAX_D;
                    y=now.y+dy[now.dir];
                    x=now.x+dx[now.dir];
                }
                now=Point(y,x,now.dir);
            }
            //printf("3:");
            printf("%d %d\n",now.x,now.y);
        };

        bfs(b,a);
    }
    return 0;
}