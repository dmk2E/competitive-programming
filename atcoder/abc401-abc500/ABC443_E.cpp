/*アルゴリズムと工夫点(Climbing Silver/CPU: 159 ms Memory: 6524 KB  Length: 1524 B)
動的計画法で解く．
問題の制約から，列ごとに，一番下の壁またはそれより低いマスに到達可能である時，その列の1行目には到達可能である．
これを活かして実装すれば，1テストケース当たりの最悪計算量は，O(N ^ 2) で，全体で 10 ^ 7 未満となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;
const int dy[] = {-1, -1, -1};
const int dx[] = {-1, 0, 1}, MAX_D = 3;

string solve(){
    int i, j, k, n, c;
    scanf("%d%d", &n, &c);
    vector<vector<bool> > mp(n, vector<bool>(n, false)), dp(n, vector<bool>(n, false));
    vector<int> w_to_min_h(n, n);
    rep(i, n){
        getchar();
        rep(j, n)mp[i][j] = getchar() == '.';
    }
    rep(j, n){
        for(i = n - 1; i >= 0 ;i--)if(mp[i][j] == false){
            w_to_min_h[j] = i;
            break;
        }
    }
    dp[n - 1][c - 1] = true;
    for(i = n - 1;i >= 0;i--){
        rep(j, n)if(dp[i][j]){
            rep(k, MAX_D){
                int y = i + dy[k];
                int x = j + dx[k];
                if(
                    0 <= y && y < n && 
                    0 <= x && x < n
                ){
                    if(mp[y][x])dp[y][x] = true;
                    else if(!dp[y][x] && y >= w_to_min_h[x]){
                        while(y >= 0){
                            dp[y][x] = true;
                            y--;
                        }
                    }
                }
            }
        }
    }
    string ans = "";
    rep(j, n)ans += dp[0][j] ? '1' : '0';
    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%s\n", solve().c_str());
    return 0;
}