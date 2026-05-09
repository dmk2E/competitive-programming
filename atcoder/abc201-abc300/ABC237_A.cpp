/*アルゴリズムと工夫点(Not Overflow/CPU: 1 ms Memory: 3672 KB  Length: 264 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    scanf("%lld",&n);
    printf("%s\n",-((ll)1<<31)<=n&&n<((ll)1<<31)?"Yes":"No");
    return 0;
}