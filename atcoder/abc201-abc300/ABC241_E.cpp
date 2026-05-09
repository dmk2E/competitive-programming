/*アルゴリズムと工夫点(Putting Candies/CPU: 147 ms Memory: 148212 KB  Length: 776 B)
ダブリングの応用で解く．
Xの値をmodNの世界で捉えれば，N個の頂点をk回巡回する問題と同義である．
よってダブリングで，dp[i][j]:頂点jから2^(i)回移動した時の，移動先
を高速に求める．また，
a[i][j]:頂点jから2^(i)回移動した時，得られるアメの数 
とすると，a[i+1][j]=a[i][j]+a[i][dp[i][j]] という遷移で求められる．
よって，最悪計算量は O(N*log2(K))
※Cだけ初見で解けなかった...悔しい
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll k;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%lld",&n,&k);
    const int MAX_D=60;
    vector<vector<int> > dp(MAX_D+1,vector<int>(n));
    vector<vector<ll> > a(MAX_D+1,vector<ll>(n));
    rep(i,n){
        scanf("%lld",&a[0][i]);
        dp[0][i]=(i+a[0][i])%n;
    }
    rep(i,MAX_D){
        rep(j,n){
            dp[i+1][j]=dp[i][dp[i][j]];
            a[i+1][j]=a[i][j]+a[i][dp[i][j]];
        }
    }
    j=0;
    rep(i,MAX_D+1){
        if((k>>i)&1){
            ans+=a[i][j];
            j=dp[i][j];
        }
    }
    printf("%lld\n",ans);
    return 0;
}