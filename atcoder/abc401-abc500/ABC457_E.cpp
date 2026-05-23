/*アルゴリズムと工夫点(Crossing Table Cloth/CPU: 94 ms Memory: 20952 KB  Length: 2358 B)
適切なデータ管理と二分探索で解く．
左端と右端の座標の値それぞれで，区間をグルーピングし，下記の2パターンに場合分けして解く．
 <i> 丁度のその区間[S, T]を覆う布が存在する場合
  その布が2枚あるか，もしくはその範囲内に別の布が存在するかで判定
 <ii>丁度のその区間[S, T]を覆う布が存在しない場合
  「Sを左端に持つ布の内，Tを超えない最大の座標を右端に持つ布」と，
  「Tを右端に持つ布の内，Sより大きい最小の座標を左端に持つ布」が共通部分を持つかで判定
各場合の処理は二分探索で実装できる．
最悪計算量は，O(N + (M + Q) * log2(M)) < 10 ^ 7 となり，高速．
※ 一つの解法で全ての場合を網羅しようとするのではなく，
※ 場合分けによりそれぞれ別々の手法を用いるのが良い
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, m, q;

int main(){
    int i;

    scanf("%d%d", &n, &m);
    vector<vector<int> > left_to_right(n), right_to_left(n);
    vector<int> min_r(n, n);
    while(m--){
        int l, r;
        scanf("%d%d", &l, &r);
        l--;r--;
        left_to_right[l].push_back(r);
        right_to_left[r].push_back(l);
        min_r[l] = min(min_r[l], r);
    }

    rep(i, n){
        sort(left_to_right[i].begin(), left_to_right[i].end());
        sort(right_to_left[i].begin(), right_to_left[i].end());
    }

    for(i = n - 2;i >= 0;i--)min_r[i] = min(min_r[i], min_r[i + 1]);

    scanf("%d", &q);
    while(q--){
        int s, t;
        scanf("%d%d", &s, &t);
        s--;t--;

        auto judge = [&](int start, int last) -> bool{
            int cnt = upper_bound(
                left_to_right[start].begin(), 
                left_to_right[start].end(), 
                last
            ) - lower_bound(
                left_to_right[start].begin(), 
                left_to_right[start].end(), 
                last
            );
            if(cnt){
                if(min_r[start] < last || (start + 1 < n && min_r[start + 1] <= last))return true;
                return cnt >= 2;
            }else{
                int left_max_len_id = lower_bound(
                    left_to_right[start].begin(), 
                    left_to_right[start].end(), 
                    last
                ) - left_to_right[start].begin();
                
                left_max_len_id--;
                if(left_max_len_id < 0)return false;

                int right_max_len_id = upper_bound(
                    right_to_left[last].begin(), 
                    right_to_left[last].end(), 
                    start
                ) - right_to_left[last].begin();

                if(right_max_len_id >= right_to_left[last].size())return false;

                return left_to_right[start][left_max_len_id] + 1 >= right_to_left[last][right_max_len_id];
            }
        };
        printf("%s\n", judge(/* start = */ s, /* last = */ t) ? "Yes" : "No");
    }
    return 0;
}