/*アルゴリズムと工夫点(Transportation Expenses/CPU: 35 ms Memory: 5696 KB  Length: 983 B)
xの値をある値tmpと固定した時，交通費補助額の総和SがM円以下にできるなら，0~tmp円の時は確実にM円以下に抑えることができる．逆に，M円以下にできないなら，tmp円以上でもM円以下にすることはできない．
このように単調性が存在するから，xの値を二分探索することを考える．
また，Sを求めるために，Aをソートして累積和をとったSumを用意しておく．この時，要素がtmpより大きい値になるA上の添え字yは，同様に二分探索で求めることができ，Sumを利用して交通費補助額の総和を高速に求めることができる．
最悪計算量はO(N+N*log2(N)+log2(N)*log2(max(Ai)*N+1))=O(N*log2(N)+log2(N)*log2(max(Ai)*N+1))≒10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
ll m;
vector<int> a;
vector<ll> sum;

int search(ll x){
    int i,left=0,right=n,mid;
    while(left<right){
        mid=(left+right)/2;
        if(a[mid]<=x)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i,j;
    ll left=0,right=(ll)(1e15),mid;
    scanf("%d%lld",&n,&m);
    a=vector<int>(n);
    sum=vector<ll>(n+1,0);
    rep(i,n){
        scanf("%d",&a[i]);
    }
    sort(a.begin(),a.end());
    rep(i,n)
        sum[i+1]=sum[i]+a[i];
    while(left<right){
        mid=(left+right)/2;
        j=search(mid);
        if(sum[j]+((ll)n-j)*mid<=m)
            left=mid+1;
        else
            right=mid;
    }
    if(right==(ll)(1e15))
        puts("infinite");
    else
        printf("%lld\n",left-1);
    return 0;
}