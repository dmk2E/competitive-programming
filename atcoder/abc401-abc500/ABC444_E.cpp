/*アルゴリズムと工夫点(Sparse Range/CPU: 313 ms Memory: 23984 KB  Length: 978 B)
尺取り法で解く．
配列A上のある半開区間[l, r) について，任意の2要素間の差の絶対値がD以上である場合を考える．
この条件は，範囲が広ければ広いほど満たしにくくなるため，lの増加に対してrも単調増加する．
また，条件を満たす[l, r)が決まっている時，[l + 1, r)も同様に条件を満たす．
従って尺取り法で解く．
この時，[l, r)が条件を満たす時，[l, r + 1)が条件を満たすかは，a[r]の値に最も近い，大きさ順で前後の値に着目すればよい．
これは二分探索で実現可能．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
※ ↑区間ごとに，値をsetで管理しているため
*/
#include<iostream>
#include<vector>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, d;

int main(){
    int i, j;
    ll ans = 0;
    scanf("%d%d", &n, &d);
    vector<int> a(n);
    set<int> v;
    rep(i, n)scanf("%d", &a[i]);
    for(int l = 0, r = 0;l < n;l++){
        auto judge = [&](int r) -> bool{
            if(r - l < 1)return true;
            auto it = v.lower_bound(a[r]);
            if(it == v.end())it--;
            if(abs((*it) - a[r]) < d)return false;
            if(it != v.begin()){
                it--;
                return abs((*it) - a[r]) >= d;
            }
            return true;
        };
        while(r < n && judge(r)){
            v.insert(a[r]);
            r++;
        }
        ans += r - l;
        v.erase(a[l]);
        if(l == r)r++;
    }
    printf("%lld\n", ans);
    return 0;
}