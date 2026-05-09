/*アルゴリズムと工夫点(Apple/CPU: 1 ms Memory: 3884 KB  Length: 262 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int x,y,n;

int main(){
    scanf("%d%d%d",&x,&y,&n);
    printf("%d\n",min(y*(n/3)+x*(n%3),n*x));
    return 0;
}