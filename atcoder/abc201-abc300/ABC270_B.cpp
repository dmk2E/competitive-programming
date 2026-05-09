/*アルゴリズムと工夫点(Hammer/CPU: 1 ms Memory: 3916 KB  Length: 405 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int x,y,z;

int main(){
    int i,now=0;
    scanf("%d%d%d",&x,&y,&z);
    if(x<0){
        x=-x;
        y=-y;
        z=-z;
    }
    if(now<=y&&y<=x)
        printf("%d\n",y<z?-1:abs(z)+abs(x-z));
    else
        printf("%d\n",x);
    return 0;
}