/*アルゴリズムと工夫点(Truck Driver/CPU: 27 ms Memory: 6448 KB  Length: 810 B)
累積和 + 二分探索で解く．
区間[l,r] について，lの値を固定した時，
<i> S[l,r]に含まれる'a'の個数がA以上になる最小のrの値を a_r
<ii> S[l,r]に含まれる'b'の個数がB未満になる最大のrの値を b_r
とすると，[a_r, l] と [i, b_r] の共通範囲の長さが条件を満たすrの個数となる．
ここで，a_r, b_rは，累積和+二分探索で高速に求められる．
これを利用し，lについて全探索して，解を求めればよい．
最悪計算量 O(N * log2(N)) < 10^7  となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,a,b;
string s;

int main(){
    int i,j;
    ll ans = 0;
    scanf("%d%d%d",&n,&a,&b);
    cin >> s;
    vector<int> sum_a(n + 1,0), sum_b(n + 1,0);
    rep(i,n){
        sum_a[i + 1] += (s[i] == 'a') + sum_a[i];
        sum_b[i + 1] += (s[i] == 'b') + sum_b[i];
    }
    rep(i,n){
        int a_r = lower_bound(sum_a.begin(),sum_a.end(),a + sum_a[i]) - sum_a.begin() - 1;
        int b_r = lower_bound(sum_b.begin(),sum_b.end(),b + sum_b[i]) - sum_b.begin() - 2;
        // [a_r, n - 1] && [i, b_r]
        ans += max(0, min(b_r,n - 1) - max(a_r,i) + 1);
    }
    printf("%lld\n",ans);
    return 0;
}