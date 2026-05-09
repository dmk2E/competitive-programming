/*アルゴリズムと工夫点(Edge Checker 2/CPU: 3 ms Memory: 3912 KB  Length: 225 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int a,b;

int main(){
    scanf("%d%d",&a,&b);
    printf("%s\n",2*a<=b&&b<=2*a+1?"Yes":"No");
    return 0;
}