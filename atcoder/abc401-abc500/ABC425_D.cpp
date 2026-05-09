/*アルゴリズムと工夫点(Ulam-Warburton Automaton/CPU: 24 ms Memory: 11988 KB  Length: 1932 B)
マス毎に塗った時刻を管理+多始点BFS で解く．
黒いマスを起点に，4隅の白いマスを塗るかどうかの判定を繰り返し行う．
この時，ある時点で条件を満たすか判定するために，マスが黒く塗られた時刻が必要となるため管理しておく．
実装は多始点BFSで行った．
最悪計算量は，O(H*W) < 10^7 となり高速．
※バーチャル参加
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<string> mp(h);
    rep(i,h)cin>>mp[i];
    auto bfs = [&]()->int{
        int i,j,ans = 0;
        const int INF = (1e9);
        const int dy[] = {-1,0,1,0},MAX_D = 4;
        const int dx[] = {0,1,0,-1};
        vector<vector<int> > painted(h,vector<int>(w,INF));
        queue<int> que;
        rep(i,h)rep(j,w){
            if(mp[i][j] == '#'){
                que.push(w*i+j);
                painted[i][j] = 0;
                ans++;
            }
        }
        auto judge = [&](int now_y,int now_x,int now_t)->bool{
            int i,cnt = 0;
            rep(i,MAX_D){
                int y = now_y+dy[i];
                int x = now_x+dx[i];
                if(
                    0 <= y && y < h && 
                    0 <= x && x < w && 
                    now_t+1 > painted[y][x]
                ){
                    cnt++;
                }                       
            }
            return cnt == 1;
        };
        while(que.size()){
            int now = que.front();que.pop();
            int now_y = now/w,now_x = now%w;
            rep(i,MAX_D){
                int y = now_y+dy[i];
                int x = now_x+dx[i];
                if(
                    0 <= y && y < h && 
                    0 <= x && x < w && 
                    painted[y][x] == INF &&
                    judge(y,x,painted[now_y][now_x])
                ){
                    que.push(y*w+x);
                    painted[y][x] = painted[now_y][now_x]+1;
                    ans++;
                }
            }
        }
        return ans;
    };
    printf("%d\n",bfs());
    return 0;
}