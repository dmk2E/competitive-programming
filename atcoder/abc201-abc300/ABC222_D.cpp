/*アルゴリズムと工夫点(Between Two Arrays/CPU: 35 ms Memory: 4000 KB  Length: 761 B)
dp[i][j]:1~i+1番目までの要素が確定していて，i+1番目の要素がjとなる数列Cの場合の数
とする動的計画法で解ける．遷移の際，dp[i-1]の累積和をとっておくことで処理を高速化でき，最悪計算量はO(NM)≒10^6 となり十分高速．
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A 3000
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
vector<int> a,b;

int main(){
    int i,j;
    vector<ll> last,now;
    scanf("%d",&n);
    a=vector<int>(n);
    b=vector<int>(n);
    rep(i,n)
        scanf("%d",&a[i]);
    rep(i,n)
        scanf("%d",&b[i]);
    last=vector<ll>(MAX_A+2,1);
    rep(i,n){
        now=vector<ll>(MAX_A+1,0);
        for(j=a[i];j<=b[i];j++){
            now[j]=last[j+1];
        }
        last=vector<ll>(MAX_A+2,0);
        rep(j,MAX_A+1)
            last[j+1]=(now[j]+last[j])%MOD;
    }
    printf("%lld\n",last[MAX_A+1]);
    return 0;
}