/*アルゴリズムと工夫点(Growth Record/CPU: 1 ms Memory: 3916 KB  Length: 317 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m,x,t,d;

int main(){
    int tf;
    scanf("%d%d%d%d%d",&n,&m,&x,&t,&d);
    tf=t-x*d;
    printf("%d\n",min(tf+x*d,tf+m*d));
    return 0;
}