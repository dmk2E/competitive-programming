/*アルゴリズムと工夫点(ABC conjecture/CPU: 93 ms Memory: 3796 KB  Length: 370 B)
1<=a<=a^(1/3)となり，1<=b<=(n/a)^(1/2)であることを利用すると，全探索で解ける．
最悪計算量の計算は難しいので割愛．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    int i,j;
    ll a,b,ans=0;
    scanf("%lld",&n);
    for(a=1;a*a*a<=n;a++){
        for(b=a;a*b*b<=n;b++){
            ans+=n/(a*b)-b+1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}