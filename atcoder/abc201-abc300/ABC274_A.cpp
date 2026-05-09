/*アルゴリズムと工夫点(Batting Average/CPU: 1 ms Memory: 3924 KB  Length: 242 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b;

int main(){
    scanf("%d%d",&a,&b);
    printf("%.3f\n",(double)b/a);
    return 0;
}