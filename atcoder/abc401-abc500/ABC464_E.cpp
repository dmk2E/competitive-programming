/*アルゴリズムと工夫点(Fill-Rect Query/CPU: 131 ms Memory: 58232 KB  Length: 945 B)
二次元累積 max を用いて解く．
長方形範囲の右下のグリッドに，操作を行った時間を書き込むことを考える．
すると，各マスの操作が行われた最終時間は，各マスから右下の長方形領域に書き込まれた時間の最大値となる．
これは右下のマスを始点として，二次元累積最大値を求めておけばよい．
最悪計算量は，O(H * W) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h, w, q;

int main(){
    int i, j;

    scanf("%d%d%d", &h, &w, &q);
    vector<vector<int> > max_time(h, vector<int>(w, 0));
    vector<char> time_to_x(q + 1);
    time_to_x[0] = 'A';
    rep(i, q){
        int r, c;
        char x;
        scanf("%d%d %c", &r, &c, &x);
        max_time[r - 1][c - 1] = i + 1;
        time_to_x[i + 1] = x;
    }

    for(i = h - 1;i >= 0;i--)for(j = w - 1;j >= 0;j--){        
        max_time[i][j] = max(max_time[i][j], max(
            i + 1 < h ? max_time[i + 1][j] : 0, 
            j + 1 < w ? max_time[i][j + 1] : 0
        ));
    }

    rep(i, h){
        rep(j, w - 1)printf("%c", time_to_x[max_time[i][j]]);
        printf("%c\n", time_to_x[max_time[i][j]]);
    }
    return 0;
}