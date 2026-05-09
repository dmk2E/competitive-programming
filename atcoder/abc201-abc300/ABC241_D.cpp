/*アルゴリズムと工夫点(Sequence Query/CPU:  ms Memory:  KB  Length:  B)
kが小さいから，setを用いて解く．
同じ値が入力される場合の対策として，(値,その時点での何番目か)かのように保持すればよい．
最悪計算量は O(Q*log2(Q))<10^7 となり高速．
*/
#include<iostream>
#include<set>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll,int> P;

int q,k;
ll x;

int main(){
    int i,j;
    scanf("%d",&q);
    set<P> v;
    map<ll,int> dic;
    const int MAX=q;
    set<P>::iterator it;
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%lld",&x);
            v.insert(P(x,dic[x]++));
        }else if(i==2){
            scanf("%lld%d",&x,&k);
            it=v.lower_bound(P(x,MAX));
            while(k--&&it!=v.begin())it--;
            printf("%lld\n",k==-1?(*it).first:-1);
        }else{
            scanf("%lld%d",&x,&k);
            it=v.lower_bound(P(x-1,MAX));
            while(--k&&it!=v.end())it++;
            printf("%lld\n",(k==0&&it!=v.end())?(*it).first:-1);
        }
    }
    return 0;
}