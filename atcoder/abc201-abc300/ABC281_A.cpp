/*アルゴリズムと工夫点(Count Down/CPU: 2 ms Memory: 3880 KB  Length: 257 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i;
    scanf("%d",&n);
    rep(i,n+1)
        printf("%d\n",n-i);
    return 0;
}