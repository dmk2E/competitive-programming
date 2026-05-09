/*アルゴリズムと工夫点(Freefall/CPU: 1 ms Memory: 4096 KB  Length: 506 B)
math.sqrt()がlong doubleに対応しておらず，その場合はdouble型の方が精度が良い．
*/
#include<iostream>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll a,b;

int main(){
    int i,j;
    scanf("%lld%lld",&a,&b);
    ll k=pow((double)a/(2*b),2.0/3.0)-1,l;
    double mmin;
    for(l=max(k-5,(ll)0),mmin=(double)l*b+(double)a/sqrt(1+l);l<k+5;l++){
        if(mmin>l*b+(double)a/sqrt(1+l))
            mmin=(double)l*b+(double)a/sqrt(1+l);
    }
    printf("%.7f\n",mmin);
    return 0;
}