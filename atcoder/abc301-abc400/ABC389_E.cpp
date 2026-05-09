/*アルゴリズムと工夫点(Square Price/CPU: 107 ms Memory: 4156 KB  Length: 1121 B)
k個買うときとk-1個買うときの値段の差分を考えて，k回目に商品を買う場合の値段がp*(2*k-1)円になる問題に帰着させて考える．
ある状態（商品をいくつか買った状態）で，最も安い商品を買っていけば，商品の購入数は最大になる．
この貪欲法では，購入する商品の値段は単調増加する．そこで，「各商品をX円未満まで買う時，M円以下にできるか」という二分探索を行う．
そうすることで，貪欲法の終盤までワープできる．
最悪計算量は O(N*(log2(M))^2)<10^8 となり高速．
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll,ll> P;

int n;
ll m;

int main(){
    int i,j;
    scanf("%d%lld",&n,&m);
    vector<int> p(n);
    rep(i,n)scanf("%d",&p[i]);
    ll left,right,mid;
    auto judge=[&](ll x)->bool{
        int i;
        ll k,sumM=0;
        rep(i,n){
            k=((x-1)/p[i]+1)/2;
            if(k<=0)continue;
            if(m/k/k/p[i]==0)return false;
            sumM+=k*k*p[i];
            if(sumM>m)return false;
        }
        return true;
    };
    left=1;
    right=m+1;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))left=mid+1;
        else right=mid;
    }
    auto count=[&](ll x)->ll{
        int i;
        ll ans=0;
        ll k;
        rep(i,n){
            k=((x-1)/p[i]+1)/2;
            m-=k*k*p[i];
            ans+=k;
        }
        return ans+m/x;
    };
    printf("%lld\n",count(left-1));
    return 0;
}