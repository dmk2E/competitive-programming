/*アルゴリズムと工夫点(^{-1}/CPU: 1 ms Memory: 3876 KB  Length: 317 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x;

int main(){
    int i,j;
    scanf("%d%d",&n,&x);
    rep(i,n){
        scanf("%d",&j);
        if(j==x)break;
    }
    printf("%d\n",i+1);
    return 0;
}