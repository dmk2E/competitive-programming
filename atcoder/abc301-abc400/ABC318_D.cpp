/*アルゴリズムと工夫点(General Weighted Max Matching/CPU: 35 ms Memory: 4116 KB  Length: 1216 B)
使用した端点の状態を頂点としてもつ有向グラフ上でBFSを用いて解く．
最悪計算量は，O(N * N * 2 ^ (N)) < 10^8 となり間に合う．
※ 処理的には公式解説のbitDPと同じ
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    const int NIL = -1;
    scanf("%d",&n);
    vector<vector<int> > adj(n,vector<int>(n,NIL));
    rep(i,n - 1)for(j = i + 1;j < n;j++){
        scanf("%d",&adj[i][j]);
        adj[j][i] = adj[i][j];
    }
    auto bfs = [&]()->ll{
        int i;
        ll ans = 0;
        vector<ll> max_w(1 << n, NIL);
        queue<int> que;
        max_w[0] = 0;
        que.push(0);
        while(que.size()){
            int now = que.front();que.pop();
            rep(i,n)if(!((now >> i) & 1)){
                rep(j,n)if(i != j && (!((now >> j) & 1))){
                    int nxt = now | (1 << i) | (1 << j);
                    if(max_w[nxt] < max_w[now] + adj[i][j]){
                        max_w[nxt] = max_w[now] + adj[i][j];
                        ans = max(ans, max_w[nxt]);
                        que.push(nxt);
                    }
                }
            }
        }
        return ans;
    };
    printf("%lld\n",bfs());
    return 0;
}