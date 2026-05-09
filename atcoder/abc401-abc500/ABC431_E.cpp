/*アルゴリズムと工夫点(Reflection on Grid/CPU: 86 ms Memory: 31788 KB  Length: 2690 B)
鏡を変更した数の最小値を"拡張0-1BFS"で解く．
各マスを頂点とみなし，どの方向から到達したのかの4パターン分頂点を拡張した有向グラフを考える．
この時辺の重みは，鏡の向きを変更する場合に「1」，そうでない場合に「0」とする．
このグラフ上で0-1BFSを解く．この時，右下の隣のマスの頂点だけ別で保持しておき，この頂点に記録される値を出力する．
最悪計算量は，O(Σ_{k = 1}^{T} 4 * H_{k} * W_{k}) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<deque>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define TYPE 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int d_id,y,x;

    Data(int y = 0, int x = 0,int d_id = 0):d_id(d_id),y(y),x(x){}
};

int t;
const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1},MAX_D = 4;
const int type[TYPE][MAX_D] = {
                                {0,1,2,3},
                                {3,2,1,0},
                                {1,0,3,2}
                            };

int solve(){
    int i,j,h,w;
    scanf("%d%d",&h,&w);
    vector<vector<int> > mp(h,vector<int>(w,0));
    rep(i,h){
        string s;
        cin >> s;
        rep(j,w){
            switch(s[j]){
                case 'A':
                    mp[i][j] = 0;
                    break;
                case 'B':
                    mp[i][j] = 1;
                    break;
                case 'C':
                    mp[i][j] = 2;
                    break;
                default:
                    assert(1);
                    break;
            }
        }
    }
    auto bfs = [&]()->int{
        int i;
        const int INF = h * w + 1;
        deque<Data> deq;
        vector<vector<vector<int> > > vis(h,vector<vector<int> >(w,vector<int>(MAX_D,INF)));
        int goal = INF;
        deq.push_front(Data(0,0,1));
        vis[0][0][1] = 0;
        while(deq.size()){
            Data now = deq.front();deq.pop_front();
            int nxt_y,nxt_x,nxt_d_id,nxt_val;
            rep(i,TYPE){
                nxt_d_id = type[i][now.d_id];
                nxt_y = now.y + dy[nxt_d_id];
                nxt_x = now.x + dx[nxt_d_id];
                nxt_val = vis[now.y][now.x][now.d_id] + (i == mp[now.y][now.x] ? 0 : 1);
                if(nxt_y == h - 1 && nxt_x == w && nxt_d_id == 1){
                    goal = min(goal,nxt_val);
                }else if(
                    0 <= nxt_y && nxt_y < h &&
                    0 <= nxt_x && nxt_x < w &&
                    nxt_val < vis[nxt_y][nxt_x][nxt_d_id]
                ){
                    if(nxt_val == vis[now.y][now.x][now.d_id]){
                        deq.push_front(Data(nxt_y,nxt_x,nxt_d_id));
                    }else{
                        deq.push_back(Data(nxt_y,nxt_x,nxt_d_id));
                    }
                    vis[nxt_y][nxt_x][nxt_d_id] = nxt_val;
                }
            }
        }
        return goal;
    };
    return bfs();
}

int main(){
    scanf("%d",&t);
    while(t--)printf("%d\n",solve());    
    return 0;
}