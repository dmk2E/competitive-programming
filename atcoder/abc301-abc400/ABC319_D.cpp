/*アルゴリズムと工夫点(Minimum Width/CPU: 47 ms Memory: 4100 KB  Length: 880 B)
二分探索で解く．
最悪計算量は，O(N * log2(MAX_W)) < 10^7 となり高速．
※ 条件式を考える時は，"探索する解"と"条件式の判定に利用する値"の関係を想像すること
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<int> l(n, 0);
    rep(i,n)scanf("%d",&l[i]);
    auto calcRow = [&](ll w) -> int{
        int i, ans = 1;
        ll now = 0;
        rep(i,n){
            if(now + l[i] <= w)now += l[i] + 1;
            else{
                ans++;
                if(l[i] > w)return m + 1;
                now = l[i] + 1;
            }
        }
        return ans;
    };
    const ll MAX_W = (1e15);
    ll left = 0, right = MAX_W;
    while(left < right){
        ll mid = (left + right) / 2;
        if(calcRow(mid) <= m)right = mid;
        else left = mid + 1;
    }
    printf("%lld\n", left);
    return 0;
}