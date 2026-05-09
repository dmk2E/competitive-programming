/*アルゴリズムと工夫点(Slot Strategy 2 (Easy) /CPU: 1 ms Memory: 3968 KB  Length: 1027 B)
全探索 + シミュレーションで解く．
スロットで揃える数字と，押すスロットの順番を固定し，シミュレーションして解く．
最悪計算量は，O(60 * 3 * M) < 10^5 となり十分高速．
※ 制約に対して高速な計算量になるのであれば，実装しやすい方針で解くことが重要
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define N 3
#define NUM 10
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int m;

int main(){
    const int INF = (1e9);
    int i,j,ans = INF;
    string perm = "";
    rep(i, N)perm += '0' + i;
    scanf("%d", &m);
    vector<string> s(N);
    rep(i, N)cin >> s[i];
    auto calc = [&](const char target, const string& perm) -> int{
        int t = 0, now_perm = 0, row = perm[0] - '0';
        while(t < 3 * m){
            int col = t % m;
            if(s[row][col] == target){
                now_perm++;
                if(now_perm == N)return t;
                row = perm[now_perm] - '0';
            }
            t++;
        }
        return INF;
    };
    do{
        rep(i, NUM)ans = min(ans, calc(i + '0', perm));
    }while(next_permutation(perm.begin(), perm.end()));
    printf("%d\n", ans == INF ? -1 : ans);
    return 0;
}