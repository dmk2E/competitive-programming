/*アルゴリズムと工夫点(Sum of Subarrays/CPU: 99 ms Memory: 14312 KB  Length: 891 B)
主客転倒 + 累積和により高速化して解く．
与えられた問題は，""区間[Li, Ri]の中であり得る全区間の和"の和"を求めるものとなっている．
そのため，Aj が何回足されるかを考える．
ここでポイントとなるのは，Ajが現れる"区間の個数"であり，これは (Ri - j + 1) * (j - Li + 1) で求められる．
よって求める解は，
Σ Aj * (Ri - j + 1) * (j - Li + 1) 
= (Ri + 1)(1 - Li) * ΣAj + (Li + Ri) * Σ(j*Aj) - Σ (j^(2) * Aj)
最悪計算量は，O(N + Q) < 10^7 となり高速．
※ 実験で数を求めるアプローチだけでなく，計算式を立て，クレバーに求めるアプローチも大事 
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<int> a(n);
    vector<ll> sum_a(n + 1, 0), sum_a_j(n + 1, 0), sum_a_j2(n + 1, 0);
    rep(i,n){
        ll a;
        scanf("%lld",&a);
        sum_a[i + 1] += sum_a[i] + a;
        sum_a_j[i + 1] += sum_a_j[i] + a * i;
        sum_a_j2[i + 1] += sum_a_j2[i] + a * i * i;
    }
    auto cal=[&](ll l, ll r)->ll{
        return (r + 1) * (1 - l) * (sum_a[r + 1] - sum_a[l]) + 
               (l + r) * (sum_a_j[r + 1] - sum_a_j[l]) - 
               (sum_a_j2[r + 1] - sum_a_j2[l]);
    };
    while(q--){
        int l, r;
        scanf("%d%d",&l,&r);l--;r--;
        printf("%lld\n",cal(l,r));
    }
    return 0;
}