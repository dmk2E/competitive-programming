/*アルゴリズムと工夫点(ロボットで効率よく物資を回収せよ！/CPU: - ms Memory: - KB  Length: - B)
グラフ生成 + 順列全探索で解く．
初期位置と物資の場所をそれぞれ頂点とし，
「ロボットが各頂点が表す地点間を行き来する際に必要な最小移動マス数」を重みとするグラフ上で本問題を考える．
このグラフ作成は，各頂点を始点としたBFSを行うことで実現できる．
物資を表す頂点数は最大10個しかないため，回収する順序を全て試し，シミュレーションを行うことで解を計算する．
ロボットが移動するマス目が，高さH, 幅W ，物資の数N とすると，
最悪計算量は，O(H * W * (N + 1) + (N + 1) * N!) < 10 ^ 8 となり，間に合う．
※ 順列全探索を再帰で実装しており，枝刈りにより，実際はより高速に動作する．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<sstream>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define INPUT_NUMBER 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class Outputer{
    vector<T> ans;

public:
    Outputer(){}

    void push(T value){
        ans.push_back(value);
    }

    void output(string prefix = "", string suffix = ""){
        int i;
        if(ans.size() > 0){
            rep(i, ans.size() - 1)cout << prefix << ans[i] << suffix << ',';
            cout << prefix << ans[i] << suffix << '\n';
        }
    }
};

// vector<string> ipt = {
//     "3 4 1X5RX00309X2",
//     "4 1 1R01",
//     "8 5 9002X01XX1X070X42X3XX00000000XX004X0090R"
// };
vector<string> ipt = {
    "5 7 4X1X30000070X0XXRX00X09X6080X05X200",
    "8 7 00009X099X0XX00XX90000X99XXRXX000000000X0X0XX0X99X9X9000",
    "9 9 600X000X90X0X1X3X00X4X0X0X00X0X0X0X00X0XRX0X00X0X5X0X00X0X0X6X00X2X0X0X08X000X007"
};
Outputer<int> answer;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto ss = stringstream(ipt[ipt_id]);

        int w, h;
        string mp_line;
        ss >> w >> h >> mp_line;
        
        // 入力データ整形
        vector<string> mp(h);
        const int NIL = -1;
        vector<int> node_y, node_x, pos_to_node_id(h * w, NIL);
        int start_y, start_x;
        rep(i, h){
            mp[i] = mp_line.substr(i * w, w);
            rep(j, w){
                if('1' <= mp[i][j] && mp[i][j] <= '9'){
                    pos_to_node_id[i * w + j] = node_y.size();
                    node_y.push_back(i);
                    node_x.push_back(j);
                }else if(mp[i][j] == 'R'){
                    start_y = i;
                    start_x = j;
                }
            }
        }
        pos_to_node_id[start_y * w + start_x] = node_y.size();
        node_y.push_back(start_y);
        node_x.push_back(start_x);

        // グラフ作成
        int num_node = node_y.size();
        vector<vector<int> > adj(num_node, vector<int>(num_node, 0));
        auto bfs = [&](int start_node) -> void{
            const int NIL = -1;
            const int dy[] = {-1, 0, 1, 0};
            const int dx[] = {0, 1, 0, -1}, MAX_D = 4;
            vector<vector<int> > vis(h, vector<int>(w, NIL));
            queue<int> que;

            vis[node_y[start_node]][node_x[start_node]] = 0;
            que.push(node_y[start_node] * w + node_x[start_node]);
            adj[start_node][start_node] = 0;
            while(que.size()){
                int y = que.front() / w;
                int x = que.front() % w;
                que.pop();

                int i;
                rep(i, MAX_D){
                    int nxt_y = y + dy[i];
                    int nxt_x = x + dx[i];
                    if(
                        0 <= nxt_y && nxt_y < h && 
                        0 <= nxt_x && nxt_x < w &&
                        mp[nxt_y][nxt_x] != 'X' &&  
                        vis[nxt_y][nxt_x] == NIL
                    ){
                        int pos = nxt_y * w + nxt_x;
                        que.push(pos);
                        vis[nxt_y][nxt_x] = vis[y][x] + 1;

                        if('1' <= mp[nxt_y][nxt_x] && mp[nxt_y][nxt_x] <= '9')
                            adj[start_node][pos_to_node_id[pos]] = vis[nxt_y][nxt_x];
                        else if(mp[nxt_y][nxt_x] == 'R')
                            adj[start_node][num_node - 1] = vis[nxt_y][nxt_x];
                    }
                }
            }
        };
        rep(i, num_node)bfs(/* start_node = */ i);

        // 順列全探索
        const ll MAX_COST = 1e18;
        ll ans = MAX_COST;
        const int BASE_ENERGY = 1000;
        auto dfs = [&](auto& func, int now_node, int state, ll cost, ll sum_weight) -> void{
            int i;

            if(state == (1 << (num_node - 1)) - 1){
                ll add_cost = (sum_weight + BASE_ENERGY) * adj[now_node][num_node - 1];
                ans = min(ans, cost + add_cost);
                return ;
            }

            rep(i, num_node - 1)if(!((state >> i) & 1)){
                ll add_cost = (sum_weight + BASE_ENERGY) * adj[now_node][i];
                if(cost + add_cost < ans)
                    func(
                        /* func = */ func, 
                        /* now_node = */ i, 
                        /* state = */ state | (1 << i), 
                        /* cost = */ cost + (sum_weight + BASE_ENERGY) * adj[now_node][i], 
                        /* sum_weight = */ sum_weight + (mp[node_y[i]][node_x[i]] - '0')
                    );
            }
        };
        dfs(
            /* func = */ dfs, 
            /* now_node = */ num_node - 1, 
            /* state = */ 0, 
            /* cost = */ 0, 
            /* sum_weight = */ 0
        );

        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}