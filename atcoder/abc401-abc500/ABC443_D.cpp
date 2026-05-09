/*アルゴリズムと工夫点(Pawn Line/CPU: 20 ms Memory: 6040 KB  Length: 719 B)
2回走査して解く．
最終的に各列に存在する駒が描く線は山と谷を繰り返すもので，広義単調減少と広義単調増加の2パターンが繰り返される．
この場合，左→右への走査と右→左への走査の2回で解を求めることができる．
最悪計算量は，O(Σ(i ∈ [0, T)) Ni) < 10 ^ 6 となり高速．
※ 値の更新を工夫することで，単純な2回走査で解を求めることができる点は覚えておく
※ DPのように確定済みの情報を伝播させていくイメージ
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

ll solve(){
    int i, start, n;
    ll ans = 0;
    const int NIL = -1;
    scanf("%d", &n);
    vector<int> row(n), target_row;
    rep(i, n)scanf("%d", &row[i]);
    target_row = row;
    rep(i, n - 1)target_row[i + 1] = min(target_row[i + 1], target_row[i] + 1);
    for(i = n - 1; i > 0 ;i--)target_row[i - 1] = min(target_row[i - 1], target_row[i] + 1);
    rep(i, n)ans += row[i] - target_row[i];
    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%lld\n", solve());
    return 0;
}