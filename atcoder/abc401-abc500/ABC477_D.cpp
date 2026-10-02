/*アルゴリズムと工夫点(Masking Tape/CPU: 31 ms Memory: 5112 KB  Length: 1184 B)
時系列の導入 + シミュレーション で解く．
タイルがおかれる瞬間に，そのマスの色を更新していくことを考える．
この時，タイルがおかれていない期間に色の変更があったか判定する必要があるため，各クエリに時系列を導入する．
直前のクエリ2により塗られた色Cの情報と時間を保持しつつ，クエリ1の度にCで塗るか判定すればよい．
 ・判定条件は，「タイルが取り除かれたタイミングより後に，クエリ2があったか」
全クエリ終了後に，改めて全マスについて色を塗るかの判定を1回行う必要があることに注意．
最悪計算量は，O(N + Q) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, q;

int main(){
    int i;

    scanf("%d%d", &n, &q);
    string ans = string(/* count = */ n, /* ch = */ 'a');
    
    const int NIL = -1;
    vector<int> last_not_covered_time(n, NIL);
    vector<bool> is_covered(n, false);
    int last_paint_time = NIL;
    char last_paint_color = 'a';
    rep(i, q){
        int type;
        scanf("%d", &type);

        if(type == 1){
            int x;
            scanf("%d", &x);
            x--;

            if(is_covered[x])last_not_covered_time[x] = i;
            else if(last_not_covered_time[x] < last_paint_time)ans[x] = last_paint_color;

            is_covered[x] = !is_covered[x];
        }else{
            char c;
            scanf(" %c", &c);
            last_paint_time = i;
            last_paint_color = c;
        }
    }
    rep(i, n)if(
        !is_covered[i] && 
        last_not_covered_time[i] < last_paint_time
    )ans[i] = last_paint_color;

    cout << ans << endl;
    return 0;
}