/*アルゴリズムと工夫点(Max Multiple/CPU: 4 ms Memory: 3900 KB  Length: 825 B)
dp[i][j][k]:a1~aiの範囲で，k個選んだ時の和αとし，αで割った余りがjであるものの，αの最大値
とする動的計画法で解ける．
Dの倍数を答える問題であるから，[a1,ai-1]までの範囲において，Dで割った時の余りと選んだ個数kが同一であるαについて，最大のもののみを保持して置けば，新たにaiが追加された時のDPテーブルを適切に求められる．
最悪計算量はO(NKD)≒10^6 となり，十分高速．
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k,d,a;

int main(){
    int i,j,kk;
    ll tmp;
    scanf("%d%d%d",&n,&k,&d);
    const int NIL=-1;
    vector<vector<ll> > last(d,vector<ll>(k+1,NIL));
    last[0][0]=0;
    rep(i,n){
        scanf("%d",&a);
        vector<vector<ll> > now(d,vector<ll>(k+1,NIL));
        rep(j,d)rep(kk,k+1){
            if(now[j][kk]<last[j][kk])
                now[j][kk]=last[j][kk];
            if(kk+1<=k&&last[j][kk]!=NIL){
                tmp=last[j][kk]+a;
                if(now[tmp%d][kk+1]<tmp)
                    now[tmp%d][kk+1]=tmp;
            }
        }
        swap(last,now);
    }
    printf("%lld\n",last[0][k]);
    return 0;
}