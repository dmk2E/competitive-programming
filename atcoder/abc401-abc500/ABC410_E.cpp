/*アルゴリズムと工夫点(Battles in a Row/CPU: 11 ms Memory: 3876 KB  Length: 758 B)
動的計画法で解く．
dp[i][j]:i番目のモンスターを倒した時，体力がjの場合で，最大の魔力値
というテーブルを，途中で敵を倒せなくなるまで埋めていく．
最悪計算量は O(N*H)<10^7 となり高速．
※実装に工夫がいるDPの問題
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,h,m,a,b;

int main(){
    int i,j;
    const int NIL=-1;
    scanf("%d%d%d",&n,&h,&m);
    vector<int> dp(h+1,NIL);
    dp[h]=m;
    rep(i,n){
        bool can_defeat=false;
        scanf("%d%d",&a,&b);
        vector<int> now(h+1,NIL);
        rep(j,h+1){
            if(dp[j]!=NIL){
                if(j-a>=0)now[j-a]=max(now[j-a],dp[j]),can_defeat=true;
                if(dp[j]-b>=0)now[j]=max(now[j],dp[j]-b),can_defeat=true;
            }
        }
        if(!can_defeat)break;
        swap(dp,now);
    }
    printf("%d\n",i);
    return 0;
}