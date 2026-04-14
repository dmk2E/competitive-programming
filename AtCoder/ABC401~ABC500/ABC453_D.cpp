/*アルゴリズムと工夫点(Go Straight/CPU: 347 ms Memory: 95524 KB  Length: 3558 B)
拡張BFS + 経路復元 で解く．
各マスを頂点で表し，どの方向から侵入したかの4通り分だけ，
頂点を増やした有向重み無しグラフ上で，'S' -> 'G'への最短距離を求めればよい．
これは拡張BFS で求めることができる．
各マスの訪問状況は，各マスに対応する H * W * 4 の3次元配列にて，直前にいた頂点情報を持つことで実現する．
そうすると，経路復元時はこのテーブルを元に行えばよい．
最悪計算量は，O(4 * H * W) ≒ 10 ^ 7 となり高速．
※ 方針は単純だが，実装が重い良問
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Info{
    int y, x, dirc;

    Info(int y = 0, int x = 0, int dirc = 0):y(y), x(x), dirc(dirc){}
};

int h, w;

int main(){
    int i, j;
    scanf("%d%d", &h, &w);
    vector<string> mp(h);
    int sy, sx;
    rep(i, h){
        cin >> mp[i];
        rep(j, w)if(mp[i][j] == 'S'){
            sy = i;
            sx = j;
        }
    }

    const int dy[] = {-1, 0, 1, 0}, MAX_D = 4;
    const int dx[] = {0, 1, 0, -1}, NIL = -1;
    string dirc_id_to_char = "URDL";
    Info goal, NIL_INFO = Info(/* y = */ NIL, /* x = */ NIL, /* dirc = */ NIL);
    vector<vector<vector<Info> > > vis(h, vector<vector<Info> >(w, vector<Info>(MAX_D, NIL_INFO)));
    
    auto canMove = [&](int y, int x) -> bool{
        return 0 <= y && y < h && 0 <= x && x < w && mp[y][x] != '#';
    };
    auto bfs = [&](Info now) -> bool{
        int i, j;
        queue<Info> que;
        vis[now.y][now.x][now.dirc] = now;
        que.push(now);
        while(que.size()){
            now = que.front();que.pop();
            auto [now_y, now_x, now_dirc] = now;
            int nxt_y, nxt_x, invalid_dirc = NIL;
            switch(mp[now_y][now_x]){
                case 'G':
                    goal = now;
                    return true;
                case 'o': 
                    nxt_y = now_y + dy[now_dirc];
                    nxt_x = now_x + dx[now_dirc];
                    if(
                        canMove(/* y = */ nxt_y, /* x = */ nxt_x) && 
                        vis[nxt_y][nxt_x][now_dirc].dirc == NIL
                    ){
                        que.push(Info(
                            /* y = */ nxt_y, 
                            /* x = */ nxt_x, 
                            /* dirc = */ now_dirc
                        ));
                        vis[nxt_y][nxt_x][now_dirc] = now;
                    }
                    break;
                case 'x':
                    invalid_dirc = now_dirc;
                default:
                    rep(i, MAX_D){
                        if(i == invalid_dirc)continue;
                        nxt_y = now_y + dy[i];
                        nxt_x = now_x + dx[i];
                        if(
                            canMove(/* y = */ nxt_y, /* x = */ nxt_x) && 
                            vis[nxt_y][nxt_x][i].dirc == NIL
                        ){
                            que.push(Info(
                                /* y = */ nxt_y, 
                                /* x = */ nxt_x, 
                                /* dirc = */ i
                            ));
                            vis[nxt_y][nxt_x][i] = now;
                        }
                    }
                    break;
            }
        }
        return false;
    };

    if(!bfs(
        /* now = */ Info(
            /* y = */ sy, 
            /* x = */ sx, 
            /* dirc = */ 0
        )
    ))puts("No");
    else{
        puts("Yes");
        string rev_ans = "";
        while(!(goal.y == sy && goal.x == sx)){
            rev_ans += dirc_id_to_char[goal.dirc];
            goal = vis[goal.y][goal.x][goal.dirc];
        }
        rep(i, rev_ans.size() - 1)printf("%c", rev_ans[rev_ans.size() - 1 - i]);
        printf("%c\n", rev_ans[rev_ans.size() - 1 - i]);
    }
    return 0;
}