/*アルゴリズムと工夫点(Pedometer/CPU: 25 ms Memory: 8864 KB  Length: 587 B)
円環では考えずらい→数直線で考えられるようにしたい．方法としては，
・ループする地点前後で場合分けする 不変量である円の長さLを用いると，0~L-1までの数直線上の任意の区間の長さxとすると，またぐ場合はL-xで表せる．
またぐ場合は，L-x≡0(mod M)より，L≡x(mod M)となる．ここで，Si,Sj(i<j)とすると，-L+Sj≡Si(mod M)と変形できるから，Sjを固定すると，左辺は定数となる．
だから，jそれぞれについて，i<jを満たすSiの中で，-L+Sjとなるiの個数を数え上げればよい．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;
vector<ll> sum;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d",&n,&m);
    vector<int> cnt(m,0);
    sum=vector<ll>(n+1);
    sum[0]=0;
    rep(i,n){
        scanf("%d",&j);
        sum[i+1]=sum[i]+j;
    }
    rep(j,n){
        ans+=cnt[sum[j]%m];
        ans+=cnt[(m-((sum[n]-sum[j])%m))%m];
        cnt[sum[j]%m]++;
    }
    printf("%lld\n",ans);
    return 0;
}