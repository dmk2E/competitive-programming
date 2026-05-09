/*アルゴリズムと工夫点(N-choice question/CPU: 1 ms Memory: 3876 KB  Length: 284 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,a,b;

int main(){
    int i,k;
    scanf("%d%d%d",&n,&a,&b);
    rep(i,n){
        scanf("%d",&k);
        if(k==a+b)
            break;
    }
    printf("%d\n",i+1);
    return 0;
}