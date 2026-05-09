/*アルゴリズムと工夫点(1111gal password/CPU: 30 ms Memory: 3776 KB  Length: 657 B)
dp[i][x]:Xi桁目まで決めた時，Xi=xである時の条件を満たす個数．
とする動的計画法で解ける．
最悪計算量は O(9*N)≒10^7 となり高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    const int MIN_X=1,MAX_X=9;
    scanf("%d",&n);
    vector<int> dp(MAX_X+1,0);
    rep(i,MAX_X+1)dp[i]=1;
    for(i=0;i<n-1;i++){
        vector<int> now=dp;
        for(j=1;j<=MAX_X;j++){
            if(j-1>=MIN_X)now[j]=(now[j]+dp[j-1])%MOD;
            if(j+1<=MAX_X)now[j]=(now[j]+dp[j+1])%MOD;
        }
        swap(now,dp);
    }
    j=0;
    rep(i,MAX_X)j=(j+dp[i+1])%MOD;
    printf("%d\n",j);
    return 0;
}