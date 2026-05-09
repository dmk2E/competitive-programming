/*アルゴリズムと工夫点(10yen Stamp/CPU: 1 ms Memory: 3948 KB  Length: 246 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int x,y;

int main(){
    scanf("%d%d",&x,&y);
    printf("%d\n",max(0,(y-x+9)/10));
    return 0;
}