/*アルゴリズムと工夫点(Index Trio/CPU: 227 ms Memory: 4208 KB  Length: 819 B)
Ai/Aj=Ak ⇔ Ai=Aj*Ak より，この条件式を満たす 1<=i,j,k<=N の組の個数を求める．
Aiを固定すると，条件を満たす(Aj,Ak)の組は，Aiの約数列挙で求めることができる．
Aj=Akならば，count(Aj)*count(Ak),Aj!=Akでcount(Aj)*count(Ak)*2 だけ解に加算すればよい．
もし，count(Ai)>1の場合はその分も考慮する．
最悪計算量は O(N*√N)<10^8 より間に合う．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A (int)(2e5)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d",&n);
    vector<int> cnt_a(MAX_A+1,0);
    auto cal=[&](int x)->ll{
        int i,j;
        ll ans=0;
        for(i=1;i<=x/i;i++){
            if(x%i==0){
                if(i==x/i)
                    ans+=(ll)cnt_a[i]*cnt_a[x/i];
                else
                    ans+=((ll)cnt_a[i]*cnt_a[x/i])*2;//i,x/i
            }
        }
        return ans;
    };
    rep(i,n){
        scanf("%d",&j);
        cnt_a[j]++;
    }
    rep(i,MAX_A+1)if(cnt_a[i]>0)ans+=cnt_a[i]*cal(i);
    printf("%lld\n",ans);
    return 0;
}