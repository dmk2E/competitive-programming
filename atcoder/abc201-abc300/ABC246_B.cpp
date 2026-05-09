/*アルゴリズムと工夫点(Get Closer/CPU: 1 ms Memory: 3752 KB  Length: 331 B)

*/
#include<iostream>
#include<cmath>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b;

int main(){
    scanf("%d%d",&a,&b);
    printf("%.10f %.10f\n",sqrt((double)a*a/(a*a+b*b)),sqrt((double)b*b/(a*a+b*b)));
    return 0;
}