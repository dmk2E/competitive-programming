/*アルゴリズムと工夫点(2^a b^2/CPU: 1 ms Memory: 3864 KB  Length: 572 B)
重複数え上げを防ぐため，表現方法を正規化する．
つまり，素因数の2は全て，2^(a)の方に吸収されるようにしておく．
最悪計算量は O(log2(N)*log2(N))<10^3 となり十分高速．
*/
#include<iostream>
#include<cmath>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    int i,j,left,right,mid;
    scanf("%lld",&n);
    ll a=2,ans=0;
    while(a<=n){
        left=0,right=(int)sqrt(n)+1;
        while(left<right){
            mid=(left+right)/2;
            if(a<=n/((2*(ll)mid+1)*(2*mid+1)))left=mid+1;
            else right=mid;
        }
        ans+=left;
        a*=2;
    }
    printf("%lld\n",ans);
    return 0;
}