/*アルゴリズムと工夫点(Minimum Swap/CPU: 21 ms Memory: 4912 KB  Length: 771 B)
BFSで解く．
[1, N]の添え字に対応する頂点それぞれについて，その添え字に位置している要素の値を持つ頂点に対して有向辺を張ったグラフを考える．
目標状態としては，各頂点がサイクルを持っている状態である．
同じサイクル内の添え字同士でswap操作を行うと，2頂点それぞれが指し示す方向を交換する操作となり，サイクル数が1増える．
最悪計算量は，O(N) < 10^6 となり十分高速．
※「現在状態と目的状態との関係性」をグラフにして考えてみるのは典型（順列が関わる場合は特に）
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll ans = 0;
    scanf("%d", &n);
    vector<int> p(n);
    vector<bool> vis(n,false);
    rep(i,n){
        scanf("%d", &p[i]);
        p[i]--;
    }
    auto bfs = [&](int now) -> int{
        int ans = 1;
        vis[now] = true;
        while(vis[p[now]] == false){
            now = p[now];
            vis[now] = true;
            ans++;
        }
        return ans;
    };
    rep(i,n)if(vis[i] == false){
        int tmp = bfs(i);
        ans += (ll)tmp * (tmp - 1) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}