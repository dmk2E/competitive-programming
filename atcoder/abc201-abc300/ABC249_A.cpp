/*アルゴリズムと工夫点(Jogging/CPU: 1 ms Memory: 3900 KB  Length: 467 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,d,e,f,x;

int main(){
    int taka,aoki;
    scanf("%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&x);
    taka=(x/(a+c))*(a*b)+min(a*b,b*(x%(a+c)));
    aoki=(x/(d+f))*(d*e)+min(d*e,e*(x%(d+f)));
    if(taka==aoki)puts("Draw");
    else printf("%s\n",taka>aoki?"Takahashi":"Aoki");
    return 0;
}