/*アルゴリズムと工夫点(Snuke Panic (1D)/CPU: 22 ms Memory: 3908 KB  Length: 793 B)
dp[i][j]:時刻tiの時点で座標jにいる時に，既に捕まえた最大のすぬけ君の大きさ
とする動的計画法で解ける．
最悪計算量は O(N*MAX_X^2)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_X 5
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,t,x,a;

int main(){
    int i,j,tt=0;
    scanf("%d",&n);
    const int NIL=-1;
    vector<ll> dp(MAX_X,NIL);
    dp[0]=0;
    while(n--){
        scanf("%d%d%d",&t,&x,&a);
        vector<ll> now=dp;
        rep(i,MAX_X){
            rep(j,t-tt+1){
                if(j>=MAX_X)break;
                if(i+j<MAX_X)now[i+j]=max(now[i+j],dp[i]);
                if(i-j>=0)now[i-j]=max(now[i-j],dp[i]);
            }
        }
        if(now[x]!=NIL)now[x]+=a;
        swap(now,dp);
        tt=t;
    }
    printf("%lld\n",max(max(dp[0],dp[1]),max(dp[2],max(dp[3],dp[4]))));
    return 0;
}