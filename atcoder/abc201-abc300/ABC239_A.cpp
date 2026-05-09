/*アルゴリズムと工夫点(Horizon/CPU: 1 ms Memory: 3828 KB  Length: 265 B)

*/
#include<iostream>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

double h;

int main(){
    scanf("%lf",&h);
    printf("%.7f\n",sqrt(h*(12800000+h)));
    return 0;
}