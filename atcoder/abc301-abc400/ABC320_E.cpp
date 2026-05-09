/*アルゴリズムと工夫点(Somen Nagashi/CPU: 116 ms Memory: 14540 KB  Length: 871 B)
2つのset を用いて解く．
各時刻で素麺が流される度に，行列の先頭の人が素麺を受け取る構造を作る．
これはsetで人の番号を管理することで実現可能．
また，素麺を受け取った後に戻ってくる処理は，時刻と戻ってくる人の番号を管理したsetを用いればよい．
最悪計算量は，O(N + M * log2(N)) < 10^7 となり高速．
※ 解説では優先度付きキューを用いていた
*/
#include<iostream>
#include<vector>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> P;//(t, id)

int n,m;

int main(){
    int i,j;
    scanf("%d%d", &n, &m);
    vector<ll> ans(n, 0);
    set<int> row;
    set<P> log;
    rep(i, n)row.insert(i);
    while(m--){
        int t, w, s;
        scanf("%d%d%d", &t, &w, &s);
        while(log.size() && log.begin() -> first <= t){
            row.insert(log.begin() -> second);
            log.erase(log.begin());
        }
        if(row.size()){
            int now_id = *row.begin();
            row.erase(row.begin());
            ans[now_id] += w;
            log.insert(P(t + s, now_id));
        }
    }
    rep(i, n)printf("%lld\n", ans[i]);
    return 0;
}