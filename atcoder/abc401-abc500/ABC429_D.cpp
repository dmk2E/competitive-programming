/*アルゴリズムと工夫点(On AtCoder Conference/CPU: 171 ms Memory: 12912 KB  Length: 1813 B)
(座標圧縮 +) 尺取り法で解く．
人の数はN個しか存在しないため，座圧してN個の配列で保持しておく．
地点の特定の範囲[Ai, Aj) に存在する人の総数sumとする．
この時，Aiを i=1,...N として順に固定し，それぞれで sum >= C となる最小のsumの値を求め，その総和を求めればよい．
ここで，Aiの増加に対してAjは単調増加する単調性が見られるため，尺取り法が有効となる．
最悪計算量は，O(N * log2(N)) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class CoordinatedCompression{
    bool initiated;
    vector<ll> xs;
public:
    CoordinatedCompression(){
        xs=vector<ll>(0);
        initiated=false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(ll x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(ll k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    ll operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
}CC;

int n,c;
ll m;

int main(){
    int i,j;
    ll ans = 0;
    CC xs;
    scanf("%d%lld%d",&n,&m,&c);
    vector<ll> a(n);
    rep(i,n){
        scanf("%lld",&a[i]);
        xs.add(a[i]);
    }
    vector<int> x_to_cnt(xs.size(), 0);
    rep(i,n)x_to_cnt[xs(a[i])]++;
    int l, r, sum = 0;
    for(l = r = 0;l < xs.size();l++){
        while(sum < c){
            sum += x_to_cnt[r];
            r = (r + 1)%xs.size();
        }
        // 地点xs[l]未満でのスタート地点の数
        ll count = l == 0 ? xs[l] + m - xs[xs.size() - 1] : xs[l] - xs[l - 1];
        ans += count * sum;
        sum -= x_to_cnt[l];
    }
    printf("%lld\n", ans);
    return 0;
}