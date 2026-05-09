/*アルゴリズムと工夫点(World Cup/CPU: 1 ms Memory: 3908 KB  Length: 258 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int y;

int main(){
    scanf("%d",&y);
    printf("%d\n",y+(4+2-(y%4))%4);
    return 0;
}