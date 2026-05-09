/*アルゴリズムと工夫点(Counterclockwise Rotation/CPU: 1 ms Memory: 4152 KB  Length: 360 B)

*/
#include<iostream>
#include<cmath>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,d;

int main(){
    scanf("%d%d%d",&a,&b,&d);
    printf("%.7f %.7f\n",a*cos(M_PI*d/180.0)-b*sin(M_PI*d/180.0),b*cos(M_PI*d/180.0)+a*sin(M_PI*d/180.0));
    return 0;
}