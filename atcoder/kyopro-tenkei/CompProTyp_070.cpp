/*アルゴリズムと工夫点(Plant Planning（★4）/CPU: 37 ms Memory: 9664 KB  Length: 1797 B)
※x,y独立で考える
※1つの軸上に複数の点が並んでいて，ある点x=aとそれらの点との距離の総和Sum(a)とするとき，x=a+1の値は，sum(a)の値と，x=aの前後に存在する点の数を用いて求めることができる．
 ※この問題において，「中央値が絶対値の最小値となる」ことは重要な性質となる．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_X (int)(1e9)
#define MIN_X (int)(-1e9)
using namespace std;
typedef long long ll;

int n;
vector<ll> x,y;

ll search(ll z,vector<ll>& p,vector<ll>& pSum){
    int left=0,right=p.size(),mid;
    ll ans;
    while(left<right){
        mid=(left+right)/2;
        if(p[mid]<=z)
            left=mid+1;
        else
            right=mid;
    }
    return pSum[pSum.size()-1]-(p.size()-left)*z-pSum[left];
}

ll searchMin(ll mid,vector<ll>& p,vector<ll>& pSum,vector<ll>& pRev,vector<ll>& pRevSum){
    //int i;for(i=-6;i<=7;i++)printf("i:%d ans:%lld-%lld=%lld dis:%lld\n",i,search(i+(ll)MAX_X,p,pSum),search(p[p.size()-1]-i-MAX_X,pRev,pRevSum),search(i+(ll)MAX_X,p,pSum)-search(p[p.size()-1]-i-MAX_X,pRev,pRevSum),search(i+(ll)MAX_X,p,pSum)+search(p[p.size()-1]-i-MAX_X,pRev,pRevSum));puts("");
    return search(mid,p,pSum)+search(p[p.size()-1]-mid,pRev,pRevSum);
}

int main(){
    int i;
    scanf("%d",&n);
    x=vector<ll>(n);
    y=vector<ll>(n);
    vector<ll> xRev(n),yRev(n);
    vector<ll> xSum(n+1),ySum(n+1),xRevSum(n+1),yRevSum(n+1);
    rep(i,n){
        scanf("%lld%lld",&x[i],&y[i]);
        x[i]-=MIN_X;
        y[i]-=MIN_X;
    }
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    xSum[0]=ySum[0]=xRevSum[0]=yRevSum[0]=0;
    rep(i,n){
        xSum[i+1]=xSum[i]+x[i];
        ySum[i+1]=ySum[i]+y[i];
        xRev[i]=x[x.size()-1]-x[x.size()-1-i];
        yRev[i]=y[y.size()-1]-y[y.size()-1-i];
        xRevSum[i+1]=xRevSum[i]+xRev[i];
        yRevSum[i+1]=yRevSum[i]+yRev[i];
    }
    printf("%lld\n",searchMin(x[(n+1)/2-1],x,xSum,xRev,xRevSum)+searchMin(y[(n+1)/2-1],y,ySum,yRev,yRevSum));
    return 0;
}