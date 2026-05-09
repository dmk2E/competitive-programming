/*アルゴリズムと工夫点(Anyway Takahashi/CPU: 1 ms Memory: 3848 KB  Length: 265 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,d;

int main(){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    printf("%d\nTakahashi\n",(a+b)*(c-d));
    return 0;
}