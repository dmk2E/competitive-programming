/*アルゴリズムと工夫点(Apple Baskets on Circle/CPU: 28 ms Memory: 6276 KB  Length: 1038 B)
まず，何回1周するかを考え，1周出来なくなるまで配列Aiを1ずつ引いていく．
この時，直接全てのAiの要素を1引くことはできないが，代わりにAiそれぞれから今まで引いた数nowを記録しておくことで，1周できなくなるまでの操作の結果をO(N)で反映できる．
その後はシミュレーションすればよい．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll,int> P;//(Ai,i)

int n;
ll k;

int main(){
    int i,j;
    ll left,right,mid,now;
    scanf("%d%lld",&n,&k);
    vector<ll> a(n);
    priority_queue<P> PQ;
    rep(i,n){
        scanf("%lld",&a[i]);
        PQ.push(P(-a[i],i));
    }
    now=0;//今まで引いた数
    while(1){
        if((int)PQ.size()*(-PQ.top().first-now)<k){
            k-=(int)PQ.size()*(-PQ.top().first-now);
            now+=-PQ.top().first-now;
            PQ.pop();
        }else{
            now+=k/(int)PQ.size();
            k-=(int)PQ.size()*(k/(int)PQ.size());
            break;
        }
    }
    rep(i,n)a[i]=max((ll)0,a[i]-now);
    rep(i,n){
        if(k<=0)break;
        if(a[i]>0){
            a[i]--;
            k--;
        }
    }
    rep(i,n-1)printf("%lld ",a[i]);
    printf("%lld\n",a[i]);
    return 0;
}