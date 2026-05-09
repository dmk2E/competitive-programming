/*アルゴリズムと工夫点(Max × Sum/CPU: 66 ms Memory: 5864 KB  Length: 1023 B)
「大きさKの部分集合」というのは，単純にK個選べばよいだけであることに注意．
a,bの添え字を合わせつつ，aの昇順にソートし，maxAiを固定した時の maxAi*sum(bi) の最小値を求めていく．
maxAiを固定すれば，添え字i以下のBiの中から小さい順にk個取り出せばよく，これは優先度付きキューを用いて実装できる．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int t,n,k;

int main(){
    int i,j;
    ll sum,ans,tmp;
    const ll INF=(ll)(1e18);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        sum=0;
        ans=INF;
        vector<P> ab(n);
        rep(i,n)scanf("%d",&ab[i].first);
        rep(i,n)scanf("%d",&ab[i].second);
        sort(ab.begin(),ab.end());
        priority_queue<int> PQ;
        rep(i,k){
            PQ.push(ab[i].second);
            sum+=ab[i].second;
        }
        while(i<n){
            if((tmp=ab[i-1].first*sum)<ans)ans=tmp;
            PQ.push(ab[i].second);
            sum+=ab[i].second;
            sum-=PQ.top();
            PQ.pop();
            i++;
        }
        if((tmp=ab[i-1].first*sum)<ans)ans=tmp;
        printf("%lld\n",ans);
    }
    return 0;
}