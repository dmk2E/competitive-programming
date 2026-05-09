/*アルゴリズムと工夫点(Generalized ABC/CPU: 1 ms Memory: 3780 KB  Length: 285 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int k;

int main(){
    int i;
    scanf("%d",&k);
    rep(i,k)
        printf("%c",(char)((int)'A'+i));
    puts("");
    return 0;
}