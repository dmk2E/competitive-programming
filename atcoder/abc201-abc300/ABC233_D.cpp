/*アルゴリズムと工夫点(Count Interval/CPU: 64 ms Memory: 17264 KB  Length: 653 B)
連続部分列の総和を高速に求めるために，数列Aの累積和を前処理で求めておく．
そうすると，求める解は sum[r+1]-sum[l]==K(0<=l<=r<=N-1) となる個数となる．
この個数を，lの値を固定して求める．lの値を固定すると，sum[r+1]=sum[l]+Kとなり，sum[r+1]の値が決まるため，この式を満たすrの個数を調べればよい．
これは値に対する個数を連想配列で持てばよい．ただし，l<=rの関係性を守るため，lの降順に逆時系列的に求めていき(平面走査)，そのたびに連想配列を更新していけばよい．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll k;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%lld",&n,&k);
    map<ll,ll> sum2Cnt;
    vector<ll> sum(n+1,0);
    sum[0]=0;
    rep(i,n){
        scanf("%lld",&sum[i+1]);
        sum[i+1]+=sum[i];
    }
    for(i=n;i>=0;i--){//k=sum[r+1]-sum[l];sum2Cnt[X]:x∈(i,N]でsum[x]=X となる個数
        ans+=sum2Cnt.find(sum[i]+k)==sum2Cnt.end()?0:sum2Cnt[sum[i]+k];
        sum2Cnt[sum[i]]++;
    }
    printf("%lld\n",ans);
    return 0;
}