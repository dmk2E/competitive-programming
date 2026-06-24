/*アルゴリズムと工夫点(Alternating Costs/CPU: 62 ms Memory: 4520 KB  Length: 1411 B)
場合分けして解く．
本問題は，x軸方向は abs(x), y軸方向は abs(y) だけ移動する必要があることから，コマの移動を x, y の値をそれぞれ1ずつ減らすことで表現する．
各移動にかかるコストは，A or B の2通りとなるため，コストの総和が最小となるコマの進め方は，下記の2ステップに分けられる．
<i> min(A, B) のコストだけ消費して，x or y のどちらが0になるまで進める
<ii> 2つの場合分けして進める（x == 0 となったと仮定して説明する）
    * if a < b ならば y を1減らす方法は下記の2パターンとなる
        - k が奇数なら，下記のうち，最小の方を選択
            - x を一旦1増やした後，y を1減らし，x をまた1減らす  = a * 3 のコスト
            - y を1減らす = b のコスト
        - k が偶数なら
            - y を1減らす = a のコスト
    * if a >= b ならば
        - k が奇数なら
            - y を1減らす = b のコスト
        - k が偶数なら，下記のうち，最小の方を選択
            - x を一旦1増やした後，y を1減らし，x をまた1減らす  = b * 3 のコスト
            - y を1減らす = a のコスト
最悪計算量は，O(T) < 10 ^ 6 となり高速．
*/
#include<iostream>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

ll solve(){
    ll a, b, x, y;
    scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
    x = abs(x);y = abs(y);

    ll add_dist = min(x, y), ans = 0;
    if(a < b)ans += a * add_dist * 2;
    else ans += b * add_dist * 2;
    x -= add_dist;
    y -= add_dist;

    if(x > 0 || y > 0){
        if(x == 0){
            if(a < b){
                if(a * 3 <= b)ans += (y / 2) * (a * 4) + (y % 2) * (a * 3);
                else ans += (y / 2) * (a + b) + (y % 2) * b;
            }else{
                y--;
                ans += b;
                if(b * 3 <= a)ans += (y / 2) * (b * 4) + (y % 2) * (b * 3);
                else ans += (y / 2) * (a + b) + (y % 2) * a;
            }
        }else{
            if(a < b){
                x--;
                ans += a;
                if(a * 3 <= b)ans += (x / 2) * (a * 4) + (x % 2) * (a * 3);
                else ans += (x / 2) * (a + b) + (x % 2) * b;
            }else{
                if(b * 3 <= a)ans += (x / 2) * (b * 4) + (x % 2) * (b * 3);
                else ans += (x / 2) * (a + b) + (x % 2) * a;
            }
        }
    }

    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%lld\n", solve());
    return 0;
}