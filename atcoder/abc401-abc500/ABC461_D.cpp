/*アルゴリズムと工夫点(Count Subgrid Sum = K/CPU: 485 ms Memory: 4856 KB  Length: 1440 B)
二次元累積和 + 尺取り法で解く．
長方形の左上の座標(y, x) を固定した時のことを考える．
長方形範囲内の累積和の値が k と定数値であるため，範囲内の累積和の値が条件を満たす時，
長方形の横方向の辺の長さ w の増加に対して，縦の長さ h は広義単調減少する．
つまり，h と累積和の値の間には単調性が見られるため，「尺取り法」が可能．
最悪計算量は，O(H * W * (H + W)) ≒ 10 ^ 8 となり，間に合う．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h, w, k;

int main(){
    int i, j;

    scanf("%d%d%d", &h, &w, &k);
    vector<vector<int> > sum(h + 1, vector<int>(w + 1, 0));
    rep(i, h){
        string s;
        cin >> s;
        rep(j, s.length())
            sum[i + 1][j + 1] = (s[j] == '1') + sum[i + 1][j] + sum[i][j + 1] - sum[i][j];
    }

    auto range_sum = [&](int begin_y, int begin_x, int end_y, int end_x) -> int{
        return sum[end_y][end_x] - sum[end_y][begin_x] - sum[begin_y][end_x] + sum[begin_y][begin_x];
    };
    ll ans = 0;
    rep(i, h)rep(j, w){
        int min_height = h - i, max_height = h - i;
        for(int len = 1;j + len <= w;len++){
            while(max_height > 0 && range_sum(
                /* begin_y = */ i, 
                /* begin_x = */ j, 
                /* end_y = */ i + max_height, 
                /* end_x = */ j + len
            ) > k)max_height--;

            while(min_height > 0 && range_sum(
                /* begin_y = */ i, 
                /* begin_x = */ j, 
                /* end_y = */ i + min_height, 
                /* end_x = */ j + len
            ) >= k)min_height--;

            ans += max_height - min_height;
        }
    }

    printf("%lld\n", ans);
    return 0;
}