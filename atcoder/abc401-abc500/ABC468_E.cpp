/*アルゴリズムと工夫点(Sum of Average/CPU: 77 ms Memory: 11284 KB  Length: 1291 B)
累積和 + 逆元 を用いて解く．
長さ毎に，各要素が何回足されるかを観察すると，下図のようにきれいな構造をしている．
```txt
要素数5の場合...
      A_1 A_2 A_3 A_4 A_5
    1  1   1   1   1   1
長  2  1   2   2   2   1
さ  3  1   2   3   2   1
    4  1   2   2   2   1
    5  1   1   1   1   1
```
この構造により，外側 -> 内側 に向かって，値が1の正方形内の要素について，
適切に和を加算していくことで，元の解を求めることを考える．
各行では，その長さで割った値を加算する必要があるが，
前処理で下記の値を求めておけば高速に計算可能．
 ・配列A の累積和
 ・[1, N] の逆元の累積和
最悪計算量は，O(N * log(N)) < 10 ^ 7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

ll power(ll x, ll a){
    ll ans = 1;

    while(a > 0){
        if(a & 1)ans = (ans * x) % MOD;
        a >>= 1;
        x = (x * x) % MOD;
    }

    return ans;
}

int main(){
    int i, j;

    scanf("%d", &n);
    vector<ll> sum_a(n + 1, 0), rev_sum(n + 1, 0);
    rep(i, n){
        ll a;
        scanf("%lld", &a);
        sum_a[i + 1] = (sum_a[i] + a) % MOD;
        rev_sum[i + 1] = (rev_sum[i] + power(/* x = */ i + 1, /* a = */ MOD - 2)) % MOD;
    }

    auto getSum = [](int start, int last, vector<ll>& sum_arr) -> ll{
        return (sum_arr[last + 1] - sum_arr[start] + MOD) % MOD;
    };
    int start = 0, last = n - 1;
    ll ans = 0;
    while(start <= last){
        ans = (ans + (getSum(
            /* start = */ start, 
            /* last = */ last, 
            /* sum_arr = */ sum_a
        ) * getSum(
            /* start = */ start, 
            /* last = */ last, 
            /* sum_arr = */ rev_sum
        )) % MOD) % MOD;
        start++;last--;
    }

    printf("%lld\n", ans);
    return 0;
}