/*アルゴリズムと工夫点(Sandwiches/CPU: 29 ms Memory: 6760 KB  Length: 993 B)
Aj の値を固定 + 差分管理で解く．
Ajの値を，A_2,A_3,...,A_{N - 1} に固定した時に，条件を満たす組の個数を求める．
この時，A[1,i), A(i,N]それぞれの範囲における，値ごとの出現個数を管理し，A_{i}からA_{i + 1}に移行する際に情報を更新する．
この情報を用いることで，A[1,i),A(i,N]それぞれからAi, Akの組のあり得る個数を毎回高速に計算することが出来る．
最悪計算量は，O(N) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll sum = 0, ans = 0;
    scanf("%d",&n);
    vector<int> left_count(n,0),right_count(n,0),a(n);
    rep(i,n){
        scanf("%d",&a[i]);
        a[i]--;
    }
    left_count[a[0]]++;
    for(i = 2;i < n;i++){
        right_count[a[i]]++;
        sum += a[0] == a[i];
    }
    for(i = 1;i < n - 1;i++){
        ans += sum - ((ll)left_count[a[i]] * right_count[a[i]]);
        sum -= (ll)left_count[a[i]] * right_count[a[i]];
        if(a[i] != a[i + 1])sum -= (ll)left_count[a[i + 1]] * right_count[a[i + 1]];
        left_count[a[i]]++;right_count[a[i + 1]]--;
        sum += (ll)left_count[a[i]] * right_count[a[i]];
        if(a[i] != a[i + 1])sum += (ll)left_count[a[i + 1]] * right_count[a[i + 1]];
    }
    printf("%lld\n",ans);
    return 0;
}