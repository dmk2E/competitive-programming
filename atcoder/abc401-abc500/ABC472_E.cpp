/*アルゴリズムと工夫点(Odd Cycle/CPU: 88 ms Memory: 45392 KB  Length: 1672 B)
二部グラフ判定とDFSを用いた閉路判定で解く．
前提として，下記の性質が成り立つ．
 「二部グラフでない」<=>「奇数個のサイクルが存在する」
従って各頂点を2色交互に塗り分けていきながらDFSを実行し，
「既に訪問済み かつ 色が交互に塗れていない」辺が存在した場合，
二部グラフでないことが確定するため，その辺を含むサイクルを出力すればよい．
1テストケース当たりの最悪計算量は，O(N + M) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

void solve(){
    int n, m;

    scanf("%d%d", &n, &m);
    vector<vector<int> > adj(n);
    while(m--){
        int a, b;
        scanf("%d%d", &a, &b);
        a--;b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    const int NIL = -1;
    vector<int> vis(n, NIL), now_nodes;
    auto dfs = [&](auto& func, int now, bool color) -> bool{
        vis[now] = color;
        now_nodes.push_back(now);

        for(int nxt : adj[now]){
            if(vis[nxt] == NIL){
                if(func(
                    /* func = */ func, 
                    /* now = */ nxt, 
                    /* color = */ !color
                ))return true;
            }else if(vis[nxt] == color){
                vector<int> ans;
                while(now_nodes.back() != nxt){
                    ans.push_back(now_nodes.back() + 1);
                    now_nodes.pop_back();
                }
                ans.push_back(nxt + 1);

                printf("%ld\n", ans.size());
                int i;
                rep(i, ans.size() - 1)printf("%d ", ans[i]);
                printf("%d\n", ans[i]);

                return true;
            }
        }

        now_nodes.pop_back();
        return false;
    };

    if(!dfs(
        /* func = */ dfs, 
        /* now = */ 0, 
        /* color = */ false
    ))printf("%d\n", NIL);
}

int main(){
    scanf("%d", &t);
    while(t--)solve();
    return 0;
}