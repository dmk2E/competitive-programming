/*アルゴリズムと工夫点(Robot Customize/CPU: 31 ms Memory: 5796 KB  Length: 1046 B)
動的計画法で解く．
（頭に付けた部品の重さの総和）<（体に付けた部品の重さの操作和）を満たすように，嬉しさを最大化する問題．
まず全ての部品を体に付けると考える．
その後頭に付けた方が嬉しさが大きい部品に関して処理をする．
ここで，「体から頭に付け替えた場合の嬉しさの増分v」と「部品の重さ」を考える．
すると，頭に付ける部品の重さの総和が，全部品の重さの総和の半分を超えないように，vの総和を最大化する問題となる．
これはナップサック問題と同様の動的計画法で解ける．
※ 考慮しなくて良いデータがないか考えるようにする
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
    ll ans = 0, sum_w = 0;
    scanf("%d",&n);
    vector<int> w;
    vector<ll> h,b;
    rep(i,n){
        int tmp_w;
        ll tmp_h,tmp_b;
        scanf("%d%lld%lld",&tmp_w,&tmp_h,&tmp_b);
        sum_w += tmp_w;
        ans += tmp_b;
        if(tmp_h > tmp_b){
            w.push_back(tmp_w);h.push_back(tmp_h);b.push_back(tmp_b);
        }
    }
    ll max_w = sum_w / 2,max_diff;
    const ll NIL = -1;
    vector<ll> dp(max_w + 1,NIL);
    dp[0] = 0;
    max_diff = 0;
    rep(i,w.size()){
        vector<ll> nxt = dp;
        rep(j,max_w + 1)if(dp[j] != NIL && j + w[i] <= max_w){
            nxt[j + w[i]] = max(nxt[j + w[i]],dp[j] + h[i] - b[i]);
            max_diff = max(max_diff, nxt[j + w[i]]);
        }
        swap(dp,nxt);
    }
    printf("%lld\n",ans + max_diff);
    return 0;
}