/*アルゴリズムと工夫点(Multiple-Free Sequences/CPU: 226 ms Memory: 58144 KB  Length: 1227 B)
多始点BFSで解く．
2つの値の組 (s_{n - 2}, s_{n - 1}) を頂点とし，漸化式に従って計算した値 s_{n} を用いて，(s_{n - 1}, s_{n}) の頂点から有向辺を張ったグラフを考える．
つまり，1組の値の遷移の逆向きに辺を張る．
このグラフ上で，(0, ?), (?, 0) の頂点を始点とした多始点BFSを行い，到達可能な頂点数は，Mの倍数を含む1組となる．
最悪計算量は，O(M ^ 2) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int m, a, b;

int calcId(int x, int y){
    return m * x + y;
}

int main(){
    int i, j;
    scanf("%d%d%d", &m, &a, &b);
    vector<vector<int> > adj(m * m);
    rep(i, m)rep(j, m){
        int now_id = calcId(i, j);
        int nxt_id = calcId(j, (a * j + b * i) % m);
        adj[nxt_id].push_back(now_id);
    }
    auto bfs = [&]() -> int{
        int i, j, valid_nodes = m * m;
        vector<bool> vis(m * m, false);
        queue<int> que;
        rep(i, m){
            int tmp = calcId(i, 0);
            vis[tmp] = true;que.push(tmp);
            tmp = calcId(0, i);
            vis[tmp] = true;que.push(tmp);
        }
        valid_nodes -= 2 * m - 1;
        while(que.size()){
            int now = que.front();que.pop();
            for(int nxt : adj[now])if(vis[nxt] == false){
                vis[nxt] = true;
                que.push(nxt);
                valid_nodes--;
            }
        }
        return valid_nodes;
    };
    printf("%d\n", bfs());
    return 0;
}