/*アルゴリズムと工夫点(2-variable Function/CPU: 115 ms Memory: 3860 KB  Length: 694 B)
aの値を0~MAX_Aの範囲で固定した時の，N<=a^(3)+a*b^(2)+a^(2)**b+b^(3)=(a+b)(a^(2)+b^(2)) を満たす最小のbの値を二分探索して解く．
オーバーフローに注意すれば，O(MAX_A*log2(MAX_B))<10^8 となり間に合う．
※公式解説は尺取り法で解いていた...
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    int i,j;
    const int MAX_A=(int)(2e6);
    ll ans=(ll)(1e18);
    scanf("%lld",&n);
    auto searchMin=[&](ll a)->ll{
        if(n<=a*a*a)return a*a*a;
        ll left=1,right=(ll)(1e9),mid;
        while(left<right){
            mid=(left+right)/2;
            if(((n+a*a+mid*mid-1)/(a*a+mid*mid))<=a+mid)right=mid;
            else left=mid+1;
        }
        return (a+left)*(a*a+left*left);
    };
    rep(i,MAX_A)ans=min(ans,searchMin(i));
    printf("%lld\n",ans);
    return 0;
}