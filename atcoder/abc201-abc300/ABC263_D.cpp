/*アルゴリズムと工夫点(Left Right Operation/CPU: 27 ms Memory: 9688 KB  Length: 703 B)
xの値を固定した時の最小値は，yが x+1<=y<=N の範囲の値だった時の数列Aの総和の最小値を求めればよい．
そのため，yのとり得る範囲が Y<=y<=N だった時の Σ(Y<=i<=N)A[i] の最小値を高速に求めることを考える．
これは累積和を用いることで，前処理・本処理共にO(N)で求めることができるから，最悪計算量は O(N)<10^6 となり十分高速．
※実装では，元の数列の総和からの差分を最小化する問題と考えて解いた．
※バーチャル参加4完
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll l,r;

int main(){
    int i,j;
    ll ans;
    scanf("%d%lld%lld",&n,&l,&r);
    vector<ll> sum(n+1),xDiff(n+1),yDiff(n+1),yDiffMin(n+1);
    sum[0]=0;
    rep(i,n){
        scanf("%d",&j);
        sum[i+1]=sum[i]+j;
    }
    rep(i,n+1){
        xDiff[i]=i*l-sum[i];
        yDiff[i]=i*r-(sum[n]-sum[n-i]);
    }
    yDiffMin[0]=yDiff[0];
    rep(i,n)yDiffMin[i+1]=min(yDiffMin[i],yDiff[i+1]);
    ans=sum[n];
    rep(i,n+1)ans=min(ans,sum[n]+xDiff[i]+yDiffMin[n-i]);
    printf("%lld\n",ans);
    return 0;
}