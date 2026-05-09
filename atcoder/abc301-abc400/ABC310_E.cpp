/*アルゴリズムと工夫点(NAND repeatedly/CPU: 17 ms Memory: 5428 KB  Length: 558 B)
DP的手法（主客転倒）で解く．
dp[i][j]::= x∈[0,i]の範囲で，f(x,i) の値がjである組の数．
各iについて，dp[i][1]の総和が解となる．
最悪計算量は，O(N)<10^7 となり高速．
※ f(i,j)∈{0,1} となり，とり得る値の種類数が2であることを利用した解法
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

int main(){
    int i,j;
    ll ans=0;
    vector<ll> dp(2,0);
    scanf("%d",&n);
    cin>>s;
    rep(i,s.length()){
        int tmp=s[i]-'0';
        if(tmp)swap(dp[0],dp[1]);
        else{
            dp[1]=dp[0]+dp[1];
            dp[0]=0;
        }
        dp[tmp]++;
        ans+=dp[1];
    }
    printf("%lld\n",ans);
    return 0;
}