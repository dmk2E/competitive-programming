/*アルゴリズムと工夫点(Pro Exam Eligibility/CPU: 303 ms Memory: 20324 KB  Length: 1680 B)
決め打ち二分探索で解く．
勝率がX以上になるとは，下記の条件式を満たすことと同値である．
 (勝利した回数) / (区間の長さ) >= X により，
 (勝利した回数) - (区間の長さ) * X >= 0
そのためS上の各要素について、"(1 if S_{i} = 'o' else 0) - X" という値に整形し，
区間和が0以上になるか区間が存在するかどうかを判定する問題になる．
この時，K回以上勝利しているかどうか，別途判定が必要である点に注意
（右端を固定し，K回以上勝利している区間の左端の中で最も右に近いものを前処理で計算しておく）．
最悪計算量は，O(N * SEARCH_CNT) < 10 ^ 8 となり，間に合う．
※ 実数を扱う二分探索では，探索回数を固定することで無限ループを回避している
※   10 ^ (-6) 未満の誤差であるため，SEARCH_CNT = 30 とすれば十分
※ 平均値のような，要素数で割った値を扱う場合は，式変形により整形した整数値で扱うようにする
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, k;
string s;

int main(){
    int i;

    cin >> n >> k >> s;
    const int NIL = -1;
    vector<int> r_to_max_l(n, NIL);
    for(int r_begin = n - 1, l_end = n - 1, i = 0;r_begin >= 0;r_begin--){
        while(i < k && l_end >= 0){
            i += s[l_end] == 'o';
            l_end--;
        }
        if(i >= k)r_to_max_l[r_begin] = l_end + 1;

        i -= s[r_begin] == 'o';
    }

    const double EPS = 1e-12;
    auto judgeLarger = [&](double win_rate) -> bool{
        int i, j;

        // 前処理
        vector<double> sum_rate(n + 1, 0.0);
        rep(i, n)sum_rate[i + 1] = sum_rate[i] + (s[i] == 'o') - win_rate;
        
        vector<int> min_sum_rate_id(n + 1);
        j = 0;
        rep(i, n + 1){
            if(sum_rate[i] - sum_rate[j] < -EPS)j = i;
            min_sum_rate_id[i] = j;
        }

        // 判定処理
        double max_val = sum_rate[n] - sum_rate[min_sum_rate_id[r_to_max_l[n - 1]]];
        for(i = n - 1;i >= 0;i--)if(r_to_max_l[i] != NIL)
            max_val = max(
                max_val, 
                sum_rate[i + 1] - sum_rate[min_sum_rate_id[r_to_max_l[i] + 1]]
            );
        return max_val >= -EPS;
    };
    int search_cnt = 30;
    double left = 0.0, right = 1.0;
    while(search_cnt--){
        double mid = (left + right) / 2;
        if(judgeLarger(/* win_rate = */ mid))left = mid;
        else right = mid;
    }

    printf("%f\n", left);
    return 0;
}