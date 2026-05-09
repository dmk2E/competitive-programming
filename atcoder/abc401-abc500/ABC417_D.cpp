/*アルゴリズムと工夫点(Takahashi's Expectation/CPU: 119 ms Memory: 45056 KB  Length: 994 B)
動的計画法で解く．
最初のテンションの値が既知である時，最終的なテンションの値を前計算で求めておくことを考える．
dp[i][j]::=(i番目のプレゼントをもらう直前で，テンションがjである時，最終的なテンションの値)
このdpは，i=n-1 から順に求めていけばよい．
また，P,A<=500 であるから，j∈[0,1000] の範囲で計算しておけばよい．
最悪計算量は，O(N*max(Pi)*2+Q*log2(N))<10^8 となり間に合う．
※ 解が簡単に求まる所から順に求めていくのが良い．そのため，前からではなく後ろから求めていく．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_P 500
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> p(n),a(n),sum_b(n+1,0);
    rep(i,n){
        scanf("%d%d%d",&p[i],&a[i],&sum_b[i+1]);
        sum_b[i+1]+=sum_b[i];
    }
    const int P=MAX_P*2;
    vector<vector<int> > dp(n,vector<int>(P+1,0));
    rep(j,P+1)dp[n-1][j]=(p[n-1]<j?max(0,j-(sum_b[n]-sum_b[n-1])):j+a[n-1]);
    for(i=n-2;i>=0;i--)rep(j,P+1)dp[i][j]=(p[i]<j?dp[i+1][max(0,j-(sum_b[i+1]-sum_b[i]))]:dp[i+1][j+a[i]]);
    scanf("%d",&q);
    while(q--){
        int x;
        scanf("%d",&x);
        i=0;
        if(x>MAX_P){
            i=lower_bound(sum_b.begin(),sum_b.end(),x-MAX_P+1)-sum_b.begin();
            i=min(i,n);
            x=max(0,x-sum_b[i]);
        }
        printf("%d\n",i<n?dp[i][x]:x);
    }
    return 0;
}