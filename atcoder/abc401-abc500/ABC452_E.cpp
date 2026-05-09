/*アルゴリズムと工夫点(You WILL Like Sigma Problem/CPU: 79 ms Memory: 9452 KB  Length: 1072 B)
式変形 + 調和級数の考えで解く．
(i mod j) = i - floor(i / j) * j であることを利用すると，
floor(i / j) * j の値には，jを固定しiを増加させた際，値に規則性が見られる．
これを利用すると，求める解は，
ΣΣ A_{i} * B_{j} * i - ΣBj * Σ Ai * (floor(i / j) * j) となり，効率的に計算が可能になる．
最悪計算量は，O(M + N * log2(M)) < 10 ^ 7 となり高速．
※ 累積和を利用して，(floor(i / j) * j) の値が同じ部分の総和をO(1)で求めていけばよい
※ 余りを扱う問題は，被除数が0からスタートさせるようにすることで考えやすくする
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, m;

int main(){
    int i, j;
    scanf("%d%d", &n, &m);
    ll mul_sum_a = 0;
    vector<ll> sum_a(n + 2, 0);
    rep(i, n){
        ll a;
        scanf("%lld", &a);
        sum_a[i + 2] = (sum_a[i + 1] + a) % MOD;

        mul_sum_a = (mul_sum_a + (i + 1) * a) % MOD;
    }
    ll sum_b = 0;
    vector<int> b(m);
    rep(i, m){
        scanf("%d", &b[i]);
        sum_b = (sum_b + b[i]) % MOD;
    }

    ll sum_to_subt = 0;
    rep(j, m){
        ll tmp = 0;
        i = 0;
        while(i < n + 1){
            int end = min(n + 1, i + j + 1);
            tmp = (tmp + i * ((MOD + sum_a[end] - sum_a[i]) % MOD)) % MOD;
            i += j + 1;
        }
        sum_to_subt = (sum_to_subt + (tmp * b[j]) % MOD) % MOD;
    }

    printf("%lld\n", (MOD + ((mul_sum_a * sum_b) % MOD) - sum_to_subt) % MOD);
    return 0;
}