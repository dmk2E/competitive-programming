/*アルゴリズムと工夫点(Round decimals/CPU: 1 ms Memory: 3872 KB  Length: 238 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

double x;

int main(){
    scanf("%lf",&x);
    printf("%d\n",(int)(x+0.5));
    return 0;
}