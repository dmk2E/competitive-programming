/*アルゴリズムと工夫点(1D Country/CPU: 142 ms Memory: 5908 KB  Length: 1070 B)
恒例の「累積和+二分探索」で解ける．
[L,R]の範囲が，配列Xの添え字の範囲に置き換えるとどうなるかは二分探索で求めることができる．
その範囲が分かれば，その範囲のPの総和を求めればよいが，高速に求める必要があるため，前処理として累積和を取っておくこと．
最悪計算量はO(N+Q*log2(N))<10^7 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q,l,r;
vector<int> x;
vector<ll> pSum;

int searchL(int z){
    int left=0,right=n,mid;
    while(left<right){
        mid=(left+right)/2;
        if(x[mid]<z)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int searchR(int z){
    int left=0,right=n,mid;
    while(left<right){
        mid=(left+right)/2;
        if(x[mid]<=z)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i,j;
    scanf("%d",&n);
    x=vector<int>(n);
    pSum=vector<ll>(n+1,0);
    rep(i,n){
        scanf("%d",&x[i]);
    }
    pSum[0]=0;
    rep(i,n){
        scanf("%lld",&pSum[i+1]);
        pSum[i+1]+=pSum[i];
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&l,&r);
        printf("%lld\n",pSum[searchR(r)]-pSum[searchL(l)]);
    }
    return 0;
}