/*アルゴリズムと工夫点(Toggle Maze/CPU: 27 ms Memory: 6872 KB  Length: 1976 B)
拡張BFSで解く．
各マスを頂点とする有向グラフ上でBFSを行うが，スイッチを押した回数が偶数か奇数かの2状態分だけ頂点数を増加させておく．
最悪計算量は，O(2*H*W) = O(H*W) < 10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

struct Data{
    bool state;
    int y,x;

    Data(bool state=false,int y=0,int x=0):state(state),y(y),x(x){};
};

int h,w;

int main(){
    int i,j,sy,sx;
    scanf("%d%d",&h,&w);
    vector<string> mp(h);
    rep(i,h){
        cin>>mp[i];
        rep(j,w)if(mp[i][j]=='S'){
            sy=i;sx=j;
        }
    }
    auto judge=[&](bool state,int y,int x)->bool{
        if(mp[y][x]=='.'||mp[y][x]=='?'||mp[y][x]=='G'||mp[y][x]=='S')return true;
        return (state==false&&mp[y][x]=='o')||(state&&mp[y][x]=='x');
    };
    auto bfs=[&](int y,int x)->int{
        const int NIL=-1,MAX_D=4;
        const int dy[]={-1,0,1,0};
        const int dx[]={0,1,0,-1};
        queue<Data> que;
        // false:o は通れる
        // true:x は通れる
        vector<vector<vector<int> > > dist(2,vector<vector<int> > (h,vector<int>(w,NIL)));
        dist[0][y][x]=0;
        que.push(Data(false,y,x));
        while(que.size()){
            Data now=que.front();que.pop();
            if(mp[now.y][now.x]=='G')return dist[now.state][now.y][now.x];
            rep(i,MAX_D){
                y=now.y+dy[i];
                x=now.x+dx[i];
                if(
                    y>=0&&y<h&&x>=0&&x<w&&
                    judge(now.state,y,x)
                ){
                    if(mp[y][x]=='?'){
                        if(dist[!now.state][y][x]==NIL)dist[!now.state][y][x]=dist[now.state][now.y][now.x]+1,que.push(Data(!now.state,y,x));
                    }else if(dist[now.state][y][x]==NIL)dist[now.state][y][x]=dist[now.state][now.y][now.x]+1,que.push(Data(now.state,y,x));
                }
            }
        }
        return NIL;
    };
    printf("%d\n",bfs(sy,sx));
    return 0;
}