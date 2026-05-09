/*アルゴリズムと工夫点(FG operation/CPU: 11 ms Memory: 3908 KB  Length: 661 B)
dp[i][j]:1～i+1回目の操作を行ったとき，一番左の値がjとなる操作手順の総数
という動的計画法で解ける．左から2番目の数がxである時，dp[i][(j+x)%10]+=dp[i-1][j],dp[i][(j*x)&10]+=dp[i-1][j]という遷移となるから，最悪計算量はO(2*10*N)≒10^6となり，十分高速．
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<ll> last(10,0);
    scanf("%d%d",&i,&j);
    last[(i+j)%10]++;
    last[(i*j)%10]++;
    n-=2;
    while(n--){
        vector<ll> now(10,0);
        scanf("%d",&j);
        rep(i,10){
            now[(i+j)%10]+=last[i];
            now[(i+j)%10]%=MOD;
            now[(i*j)%10]+=last[i];
            now[(i*j)%10]%=MOD;
        }
        swap(last,now);
    }
    rep(i,10)
        printf("%lld\n",last[i]);
    return 0;
}