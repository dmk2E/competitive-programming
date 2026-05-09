/*アルゴリズムと工夫点(183183/CPU: 790 ms Memory: 103196 KB  Length: 991 B)
連想配列を用いて解く．
本問題は，`Ai * 10 * |Aj| + Aj` がMで割り切れるような(i,j)の組を数え上げる問題となる．
従ってAi, |Aj| を固定し，条件を満たすようなAjの個数を高速に数え上げればよい．
これはmap等の連想配列を用いればよい．
最悪計算量は，O(N * log10(max(Ai)) * log2(N)) < 10^8 となり高速．
※ 計算量の許す限り，変数を固定する数を増やし，計算しやすくすることを意識する
*/
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

/// @brief 桁数を返す関数
/// @param x 0以上の整数
/// @return 桁数
int calcDigit(int x){
    int ans = 1;
    x /= 10;
    while(x > 0){
        x /= 10;
        ans++;
    }
    return ans;
}

int main(){
    int i,j;
    const int MAX_TEN = 9;
    ll power_ten[MAX_TEN + 2] = {1}, ans = 0;
    rep(i, MAX_TEN + 1)power_ten[i + 1] = power_ten[i] * 10;
    scanf("%d%d",&n,&m);
    vector<unordered_map<int, int> > digit_to_count(MAX_TEN + 2);
    vector<int> a(n);
    rep(i,n){
        scanf("%d",&a[i]);
        digit_to_count[calcDigit(a[i])][a[i] % m]++;a[i] %= m;
    }
    rep(i,n)for(j = 1 ;j < MAX_TEN + 2 ;j++)ans += digit_to_count[j][(m - ((a[i] * (power_ten[j] % m)) % m)) % m];
    printf("%lld\n",ans);
    return 0;
}