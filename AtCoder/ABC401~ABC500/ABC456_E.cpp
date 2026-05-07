/*アルゴリズムと工夫点(Endless Holidays/CPU: 2266 ms Memory: 59004 KB  Length: 2410 B)
拡張DFSで解く．
（都市, 曜日）の状態を持った頂点を考え，下記の条件を満たす場合に，頂点i -> 頂点j に辺を付ける
 ・頂点i の曜日の次の曜日を頂点jが持ち，その上で2頂点共もその曜日は休日である場合
このように拡張したグラフ上で，DFSを行い，閉路が存在するかどうかを判定すればよい．
この時，同じ経路を探索しないように，フラグを持っておくこと．
最悪計算量は，O((N + M) * W) < 10 ^ 7 となり高速．
※ ループ判定は DFS を用いて，O(N + M) で行える
※  DFS用の「頂点毎の訪問済みフラグ」を用意し，ある頂点が，
※  それまでの経路で既に訪れた頂点かの判定を高速に行う
※  （ある頂点からの分岐を終える度に，その頂点のフラグを未訪問に戻す）
※  DFS を行う経路に閉路が存在しない場合 -> O(N + M)
※  DFS を行う経路に閉路が存在する場合 -> 訪問済みの頂点を訪れた際に，即座に探索を打ち切る
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> P; // (node_id, day_id)

int t;

bool solve(){
    int i, n, m;

    scanf("%d%d", &n, &m);
    vector<vector<int> > adj(n);
    while(m--){
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    int w;
    scanf("%d", &w);
    vector<string> is_holiday(n);
    rep(i, n)cin >> is_holiday[i];

    const int NIL = -1;
    vector<vector<int> > vis(n, vector<int>(w, NIL));
    vector<vector<bool> > flag(n, vector<bool>(w, false));
    auto dfs = [&](auto& func, int now_node, int day_id, int color) -> bool{
        vis[now_node][day_id] = color;
        flag[now_node][day_id] = true;

        int nxt_day_id = (day_id + 1) % w;
        // 同じ都市に居続ける場合
        if(is_holiday[now_node][nxt_day_id] == 'o'){
            if(flag[now_node][nxt_day_id] == false){
                if(func(
                    /* func = */ func, 
                    /* now_node = */ now_node, 
                    /* day_id = */ nxt_day_id, 
                    /* color = */ color
                ))return true;
            }else return true;
        }

        // 別の都市に移る場合
        for(int nxt_node : adj[now_node]){
            if(is_holiday[nxt_node][nxt_day_id] == 'o'){
                if(flag[nxt_node][nxt_day_id] == false){
                    if(func(
                        /* func = */ func, 
                        /* now_node = */ nxt_node, 
                        /* day_id = */ nxt_day_id, 
                        /* color = */ color
                    ))return true;
                }else return true;
            }
        }

        flag[now_node][day_id] = false;
        return false;
    };

    int vis_id = 0;
    rep(i, n)if(is_holiday[i][0] == 'o' && vis[i][0] == NIL){
        if(dfs(
            /* func = */ dfs, 
            /* now_node = */ i, 
            /* day_id = */ 0, 
            /* color = */ vis_id
        ))return true;
        vis_id++;
    }
    return false;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%s\n", solve() ? "Yes" : "No");
    return 0;
}