/*アルゴリズムと工夫点(Distinct Trio/CPU: 22 ms Memory: 4168 KB  Length: 602 B)
動的計画法で楽に解けることに気づけなかった...
解は，異なる3つの整数を選ぶ方法の数を求めればよいことに気づければよかった...
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NUM 3
#define MAX_A (int)(2e5)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a_to_cnt(MAX_A,0);
    rep(i,n){
        scanf("%d",&j);
        a_to_cnt[j-1]++;
    }
    vector<ll> dp(NUM+1,0);
    dp[0]=1;
    rep(i,MAX_A){
        vector<ll> now=dp;
        rep(j,NUM)now[j+1]+=dp[j]*a_to_cnt[i];
        swap(now,dp);
    }
    printf("%lld\n",dp[NUM]);
    return 0;
}