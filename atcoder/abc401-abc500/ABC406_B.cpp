/*アルゴリズムと工夫点(Product Calculator/CPU: 2 ms Memory: 3916 KB  Length: 442 B)
オーバーフローしないように上手く式変形．
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j;
    ll now=1,a,max_sum=1;
    scanf("%d%d",&n,&k);
    while(k--)max_sum*=10;
    while(n--){
        scanf("%lld",&a);
        if((max_sum+now-1)/now<=a)now=1;
        else now=now*a;
    }
    printf("%lld\n",now);
    return 0;
}