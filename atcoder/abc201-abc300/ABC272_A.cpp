/*アルゴリズムと工夫点(Integer Sum/CPU: 1 ms Memory: 3824 KB  Length: 309 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,ans=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&j);
        ans+=j;
    }
    printf("%d\n",ans);
    return 0;
}