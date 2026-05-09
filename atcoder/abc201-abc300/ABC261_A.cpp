/*アルゴリズムと工夫点(Intersection/CPU: 1 ms Memory: 3796 KB  Length: 300 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int l1,r1,l2,r2;

int main(){
    scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
    printf("%d\n",max(0,min(r2,r1)-max(l2,l1)));
    return 0;
}