/*アルゴリズムと工夫点(Striped Horse/CPU: 17 ms Memory: 7308 KB  Length: 1062 B)
累積和を用いた全探索で解く．
この問題は，N % (2 * W) = 0 である時，先頭Wマスを黒く塗った2 * Wマスを一単位とし，敷き詰めた時の最小のコストを求める問題となる．
この時，リングバッファの様にはみ出した際は先頭に繰り越される．
敷き詰め方は，敷き詰め始める位置である2 * W通りだけ存在し，全探索すればよい．
従って，N % (2 * W) = 0 でない時は，((2 * W) - N % (2 * W)) % (2 * W) 個だけ末尾にコスト0を追加した配列を考えることで上記のアルゴリズムを適用する．
最悪計算量は，O((2 * W) * N / (2 * W)) = O(N) < 10^6 となり十分高速．
※ 公式解説では尺取り法のように，Wマスの範囲を1マスずつずらす全探索で実装していた
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;
const ll INF = (1e15);

ll solve(){
    int i, j, n, w;
    ll ans = INF;
    scanf("%d%d", &n, &w);
    vector<ll> sum_c(n + 1);
    sum_c[0] = 0;
    rep(i, n){
        scanf("%lld", &sum_c[i + 1]);
        sum_c[i + 1] += sum_c[i];
    }
    i = (2 * w - (n % (2 * w))) % (2 * w);
    while(i--)sum_c.push_back(sum_c[n]);
    n += (2 * w - (n % (2 * w))) % (2 * w);
    auto calc = [&](int l, int r) -> ll {
        r %= n;
        return l <= r ? sum_c[r] - sum_c[l] : sum_c[n] - sum_c[l] + sum_c[r];
    };
    rep(i, 2 * w){
        ll tmp = 0;
        j = i;
        do{
            // [j, j + w)
            tmp += calc(j, j + w);
            j = (j + 2 * w) % n;
        }while(j != i);
        ans = min(ans, tmp);
    }
    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%lld\n", solve());
    return 0;
}