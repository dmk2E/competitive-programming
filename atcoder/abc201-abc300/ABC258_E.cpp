/*アルゴリズムと工夫点(Packing Potatoes/CPU: 409 ms Memory: 54252 KB  Length: 1357 B)
開始位置さえ分かれば，解は高速に求めることができるから，位置ごとに頂点を持ち，頂点iを開始位置とした時の，新たな開始位置をもつfunctionalグラフを考える．
すると，ダブリングを用いることで，開始位置を高速に求められる．
最悪計算量は O(N*log2(N)+N*log2(K))
※あるiからじゃがいもを入れ始めた時の次の開始地点が分かるなら，その値を元にi+1から始めた時の値を求められる．
※累積和+二分探索で求める場合でも，毎回スタート位置を0に合わせるようなことをしなくても，一旦その位置から何周できるかを求め，足りない分を進めるようにすると実装しやすい．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q,x;
ll k;

int main(){
    int i,j,now_x;
    ll sum;
    scanf("%d%d%d",&n,&q,&x);
    vector<ll> sum_w(n+1,0);
    rep(i,n){
        scanf("%lld",&sum_w[i+1]);
        sum_w[i+1]+=sum_w[i];
    }
    vector<ll> start_to_cnt(n);
    const int MAX_K=60;
    vector<vector<int> > dp(MAX_K,vector<int>(n,0));
    rep(i,n){
        j=i;
        sum=0;
        now_x=x;
        sum+=n*(now_x/sum_w[n]);
        now_x%=sum_w[n];
        if(now_x>=sum_w[n]-sum_w[j]){
            sum+=n-j;
            now_x-=sum_w[n]-sum_w[j];
            j=0;
        }
        int left=j,right=n,mid;
        while(left<right){
            mid=(left+right)/2;
            if(sum_w[mid]-sum_w[j]<now_x)left=mid+1;
            else right=mid;
        }
        sum+=left-j;
        dp[0][i]=left%n;
        start_to_cnt[i]=sum;
        //printf("%d->%d(%lld)\n",i,dp[0][i],start_to_cnt[i]);
    }
    rep(i,MAX_K-1)rep(j,n)dp[i+1][j]=dp[i][dp[i][j]];
    while(q--){
        scanf("%lld",&k);
        k--;
        j=0;
        rep(i,MAX_K)if((k>>i)&1)j=dp[i][j];
        printf("%lld\n",start_to_cnt[j]);
    }
    return 0;
}