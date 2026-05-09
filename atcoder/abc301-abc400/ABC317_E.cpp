/*アルゴリズムと工夫点(Avoid Eye Contact/CPU: 213 ms Memory: 60136 KB  Length: 2870 B)
前処理 + BFS で解く．
人の視線も障害物として捉えたフィールド上でBFSを行い，最短距離を求めればよい．
最悪計算量は，O(H * W) < 10^7 となり高速．
※ 前処理は多始点BFSで実装した
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int y,x;

    Data(int y = 0,int x = 0):y(y),x(x){}
};

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<string> mp(h);
    vector<vector<bool> > parsed_mp(h,vector<bool>(w,true));
    rep(i,h)cin>>mp[i];
    const int dy[] = {-1,0,1,0},MAX_D = 4;
    const int dx[] = {0,1,0,-1},NIL = -1;
    // Preprocess
    {
        struct Data{
            int y,x,id;

            Data(int y = 0,int x = 0,int id = 0):y(y),x(x),id(id){}
        };
        queue<Data> que;
        int i,j;
        // Make a flag map with imos-method
        rep(i,h)rep(j,w){
            int id = NIL;
            switch(mp[i][j]){
                case '^':
                    id = 0;
                    break;
                case '>':
                    id = 1;
                    break;
                case 'v':
                    id = 2;
                    break;
                case '<':
                    id = 3;
                    break;
                default:
                    break;
            }
            if(id != NIL){
                parsed_mp[i][j] = false;
                que.push(Data(i,j,id));
            }
        }
        while(que.size()){
            Data now = que.front();que.pop();
            int y = now.y + dy[now.id];
            int x = now.x + dx[now.id];
            if(
                0 <= y && y < h &&
                0 <= x && x < w &&
                mp[y][x] == '.'
            ){
                que.push(Data(y,x,now.id));
                parsed_mp[y][x] = false;
            }
        }
        rep(i,h)rep(j,w)if(mp[i][j] == '#')parsed_mp[i][j] = false;
    }
    int sy,sx,gy,gx;
    rep(i,h)rep(j,w){
        if(mp[i][j] == 'S')sy = i, sx = j;
        if(mp[i][j] == 'G')gy = i, gx = j;
    }
    auto bfs = [&](int y,int x,int gy,int gx)->int{
        int i;
        Data now;
        queue<Data> que;
        vector<vector<int> > dist(h,vector<int>(w,NIL));
        dist[y][x] = 0;
        que.push(Data(y,x));
        while(que.size()){
            now = que.front();que.pop();
            rep(i,MAX_D){
                y = now.y + dy[i];
                x = now.x + dx[i];
                if(
                    0 <= y && y < h &&
                    0 <= x && x < w &&
                    parsed_mp[y][x] &&
                    dist[y][x] == NIL
                ){
                    que.push(Data(y,x));
                    dist[y][x] = dist[now.y][now.x] + 1;
                }
            }
        }
        return dist[gy][gx];
    };
    printf("%d\n",bfs(sy,sx,gy,gx));
    return 0;
}