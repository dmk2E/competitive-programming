/*アルゴリズムと工夫点(Marking/CPU: 47 ms Memory: 3852 KB  Length: 367 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int t,n,d,k;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int main(){
    int g;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&d,&k);
        k--;
        g=n/gcd(n,d);
        printf("%lld\n",(long long)d*k%n+k/g);
    }  
    return 0;
}