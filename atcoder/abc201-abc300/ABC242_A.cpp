/*アルゴリズムと工夫点(T-shirt/CPU: 1 ms Memory: 3876 KB  Length: 282 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,x;

int main(){
    scanf("%d%d%d%d",&a,&b,&c,&x);
    printf("%.7f\n",x<=a?1.0:(x<=b?(double)c/(b-a):0.0));
    return 0;
}