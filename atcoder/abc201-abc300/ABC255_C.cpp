/*アルゴリズムと工夫点(±1 Operation 1/CPU: 1 ms Memory: 3784 KB  Length: 566 B)
範囲の最小値l=min(a,a+d*(n-1)), 最大値r=max(a,a+d*(n-1)) とする．
x∈[l,r] でないなら，両端のどちらか近い方に合わせるのが最適．
x∈[l,r] であるなら，lが原点となるようにlとxを平行移動し，かつ公差が正となるように考えると楽に求められる．
最悪計算量は O(1)で十分高速．
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll x,a,d,n;

int main(){
    int i,j;
    scanf("%lld%lld%lld%lld",&x,&a,&d,&n);
    ll l=min(a,a+d*(n-1)),r=max(a,a+d*(n-1));
    if(l<=x&&x<=r){
        if(d<0)d=-d;
        x-=l;
        l=0;
        if(d==0)printf("%lld\n",abs(l-x));
        else printf("%lld\n",min(x-(x/d)*d,((x/d)+1)*d-x));
    }else if(x<l)printf("%lld\n",l-x);
    else if(r<x)printf("%lld\n",x-r);
    return 0;
}