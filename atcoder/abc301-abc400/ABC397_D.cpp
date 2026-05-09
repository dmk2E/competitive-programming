/*アルゴリズムと工夫点(Cubes/CPU: 4 ms Memory: 3916 KB  Length: 735 B)
x^3-y^3=(x-y)(x^2-xy+y^2)=N>0 より，
x>yであるから，x=y+d (d:正の整数) とし，式変形を行うと，
x^3-y^3=(y+d)^3-y^3=3dy^2+(3d^2)y+d^3 =N となるから，d<N^(1/3)
d=1 の時，3y^2+3y+1=3(y+1/2)^2 + 1/4 =N より，y<N^(1/2)
※ 正の値のみを持つ変数から成る形に式を変形してみるのが良い．
※ 両辺を共通変数dで割ることで，オーバーフローを防いでいる．
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
    int i,j;
    ll left,right,mid,d=0;
    scanf("%lld",&n);
    auto f=[](ll d,ll y)->ll{
        return 3*y*y+(3*d)*y+d*d;
    };
    for(d=1;d*d*d<=n;d++){
        if(n%d>0)continue;
        left=1;
        right=(ll)sqrt(n)+1;
        while(left<right){
            mid=(left+right)/2;
            if(f(d,mid)<n/d)left=mid+1;
            else right=mid;
        }
        if(f(d,left)==n/d){
            printf("%lld %lld\n",left+d,left);
            return 0;
        }
    }
    puts("-1");
    return 0;
}