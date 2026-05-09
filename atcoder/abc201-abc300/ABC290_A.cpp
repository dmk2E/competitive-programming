/*アルゴリズムと工夫点(Contest Result/CPU: 1 ms Memory: 3880 KB  Length: 322 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,m,a[100];

int main(){
    int i,sum=0;
    scanf("%d%d",&n,&m);
    rep(i,n){
        scanf("%d",&a[i]);
    }
    while(m--){
        scanf("%d",&i);
        sum+=a[i-1];
    }
    printf("%d\n",sum);
    return 0;
}