/*アルゴリズムと工夫点(Complete Binary Tree/CPU: 56 ms Memory: 3836 KB  Length: 869 B)
頂点X からスタートして，順次親の頂点に移っていき，
元居た頂点とは兄弟の頂点を根とする木の中で，解となる頂点数を数え上げていけばよい．
最悪計算量は，O(T * log2(N) ^ 2) < 10 ^ 8 となり間に合う．
※ 解の様子を観察することで，方針が立つ場合がある
*/
#include<iostream>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

ll solve(){
    ll n, x, k;
    scanf("%lld%lld%lld", &n, &x, &k);

    auto calcNodes = [&](ll root, ll dist) -> ll{
        ll left = root, right = root;
        
        while(dist--){
            if(left > n / 2)return 0;
            left = 2 * left;
            right = 2 * right + 1;
        }
        return min(n, right) - left + 1;
    };

    ll ans = calcNodes(/* root = */ x, /* dist = */ k);
    while(x > 1 && k >= 2){
        ans += calcNodes(/* root = */ x ^ 1, /* dist = */ k - 2);
        x >>= 1;k--;
    }
    ans += (x != 1 && k == 1);
    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%lld\n", solve());
    return 0;
}