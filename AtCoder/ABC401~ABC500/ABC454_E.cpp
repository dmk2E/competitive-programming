/*アルゴリズムと工夫点(LRUD Moving/CPU: 4 ms Memory: 6092 KB  Length: 1627 B)
2行・2列ずつシミュレーションして解く．
初期位置と到着位置それぞれから，互いに座標(A, B) に少しずつ近づいていき，そのマスを含む 2 * 2 マスの領域まで詰める．
その後，場合分けで経路を決定する．
ポイントは，初期位置から詰めていく際に，問題設定を更新していくことで，処理を単純にしている点．
最悪計算量は，O(T * N ^ 2) < 10 ^ 7 となり高速．
※ グリッド上の移動は，各マスを市松模様（白黒に塗るとする）に塗った上で考察することが有効である場合がある
※  今回の場合，上下移動をすることを考えると，白と黒を交互に訪れることになる
※  初期位置と到着位置は同じ色になるはずであるため，N が奇数であったり，(A, B)の値によっては無効値となる
*/
#include<iostream>
#include<algorithm>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

void solve(){
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    
    if(n % 2 == 1 || (a + b) % 2 == 0){
        puts("No");
        return ;
    }

    int h = n, w = n;
    string ans_head = "", ans_rev_tail = "";
    while(1){
        if(a > 2){
            ans_head += string(/* count = */ w - 1, /* ch = */ 'R') + 'D';
            ans_head += string(/* count = */ w - 1, /* ch = */ 'L') + 'D';
            h -= 2;a -= 2;
        }else if(a <= h - 2){
            ans_rev_tail += string(/* count = */ w - 1, /* ch = */ 'R') + 'D';
            ans_rev_tail += string(/* count = */ w - 1, /* ch = */ 'L') + 'D';
            h -= 2;
        }else if(b > 2){
            ans_head += string(/* count = */ h - 1, /* ch = */ 'D') + 'R';
            ans_head += string(/* count = */ h - 1, /* ch = */ 'U') + 'R';
            w -= 2;b -= 2;
        }else if(b <= w - 2){
            ans_rev_tail += string(/* count = */ h - 1, /* ch = */ 'D') + 'R';
            ans_rev_tail += string(/* count = */ h - 1, /* ch = */ 'U') + 'R';
            w -= 2;
        }else{
            if(a == 1)ans_head += "DR";
            else ans_head += "RD";
            break;
        }
    }
    reverse(ans_rev_tail.begin(), ans_rev_tail.end());
    string ans = ans_head + ans_rev_tail;
    puts("Yes");
    cout << ans << '\n';
}

int main(){
    scanf("%d", &t);
    while(t--)solve();
    return 0;
}