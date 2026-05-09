/*アルゴリズムと工夫点(Bonus EXP/CPU: 26 ms Memory: 3936 KB  Length: 585 B)
dp[i][j]:敵1～iを逃がすか倒すかした時，倒した敵の数がj(0<=j<=1 奇数:0,偶数:1)の時の最大の経験値
とする動的計画法で解ける．最悪計算量O(N*2)=O(N)<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,a;
    scanf("%d",&n);
    vector<ll> last(2);
    scanf("%d",&a);
    last[0]=a;last[1]=0;
    rep(i,n-1){
        scanf("%d",&a);
        vector<ll> now=last;
        rep(j,2)
            if(now[(j+1)%2]<last[j]+a+(j==0?a:0)){
                now[(j+1)%2]=last[j]+a+(j==0?a:0);
            }
        last=now;
    }
    printf("%lld\n",max(last[0],last[1]));
    return 0;
}