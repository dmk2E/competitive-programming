/*アルゴリズムと工夫点(Alphabet Tiles/CPU: 65 ms Memory: 3968 KB  Length: 1372 B)
dp[i][j]:文字種iまで使って，j文字置いた時の，あり得る文字列の数 とする動的計画法で解く．
※前の行しか遷移に使わないdpは，1次元配列のdpを用意して，毎回次の行のdpを計算するときに，新しく全てが初期化された一次元配列oldを用意し，swap(old,dp)することで，更新をしやすくできる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_ALFA 26
using namespace std;

const int MAX=(int)(1e4);
const int MOD=998244353;

int fac[MAX],finv[MAX],inv[MAX];

int power(int x,int a){
    if(a==0)
        return 1;
    int res=power((((long long)x%MOD)*(x%MOD))%MOD,a/2);
    if(a%2==1)res=((long long)res*(x%MOD))%MOD;
    return res;
}

void initComb(){
    int i;
    fac[0]=fac[1]=1;
    finv[0]=finv[1]=1;
    inv[0]=inv[1]=1;
    for(i=2;i<MAX;i++){
        fac[i]=((long long)fac[i-1]*(i%MOD))%MOD;
        inv[i]=power(i,MOD-2);
        finv[i]=((long long)finv[i-1]*inv[i])%MOD;
    }
}

int comb(int n,int k){
    if(n<k)return 0;
    if(n<0||k<0)return 0;
    return ((long long)fac[n]*(((long long)finv[n-k]*finv[k])%MOD))%MOD;
}

int k,c[MAX_ALFA];

int main(){
    int i,j,a;
    scanf("%d",&k);
    initComb();
    rep(i,MAX_ALFA)
        scanf("%d",&c[i]);
    vector<int> dp(k+1,0);
    dp[0]=1;
    for(i=0;i<MAX_ALFA;i++){
        vector<int> old(k+1,0);
        swap(dp,old);
        rep(j,k+1){
            rep(a,c[i]+1){
                if(j+a>k)break;
                dp[j+a]=(dp[j+a]+((long long)old[j]*comb(j+a,a))%MOD)%MOD;
            }
        }
    }
    a=0;
    rep(i,k)a=((long long)a+dp[i+1])%MOD;
    printf("%d\n",a);
    return 0;
}