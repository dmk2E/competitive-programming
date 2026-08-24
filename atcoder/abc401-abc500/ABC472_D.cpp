/*アルゴリズムと工夫点(Bomber Mad/CPU: 29 ms Memory: 15984 KB  Length: 1745 B)
多始点BFSで解く．
「安全でない空マス」->「安全な空マス」への移動がK回以内で可能であるなら，
逆方向にも同様に可能である．
従って，安全な空マス群を始点とする多始点BFSを行うことで，
グリッド上で，始点からK回以内で到達可能なマスの数を求めることが出来る．
最悪計算量は，O(H * W) < 10 ^ 7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> P;

int h, w, k;

int main(){
    int i, j;

    scanf("%d%d%d", &h, &w, &k);
    vector<bool> bomb_y(h, false), bomb_x(w, false);
    vector<vector<bool> > mp(h, vector<bool>(w, false));
    rep(i, h){
        string s;
        cin >> s;

        rep(j, w)if(s[j] == '#'){
            bomb_y[i] = true;
            bomb_x[j] = true;
            mp[i][j] = true;
        }
    }

    const int NIL = -1;
    vector<vector<int> > vis(h, vector<int>(w, NIL));
    const int dy[] = {-1, 0, 1, 0}, MAX_D = 4;
    const int dx[] = {0, 1, 0, -1};
    auto bfs = [&]() -> void{
        int i, j;

        queue<P> que;
        rep(i, h)rep(j, w)if(bomb_y[i] == false && bomb_x[j] == false){
            vis[i][j] = k;
            que.push(P(i, j));
        }

        while(que.size()){
            auto [y, x] = que.front();que.pop();

            rep(i, MAX_D){
                int nxt_y = y + dy[i];
                int nxt_x = x + dx[i];

                if(
                    0 <= nxt_y && nxt_y < h && 
                    0 <= nxt_x && nxt_x < w && 
                    mp[nxt_y][nxt_x] == false && 
                    vis[nxt_y][nxt_x] == NIL
                ){
                    vis[nxt_y][nxt_x] = vis[y][x] - 1;
                    if(vis[nxt_y][nxt_x] > 0)que.push(P(nxt_y, nxt_x));
                }
            }
        }
    };
    bfs();
    
    int ans = 0;
    rep(i, h)rep(j, w)ans += vis[i][j] != NIL;
    printf("%d\n", ans);
    return 0;
}