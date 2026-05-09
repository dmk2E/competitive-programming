/*アルゴリズムと工夫点(A27 - Calculate GCD/CPU: 3 ms Memory: 3944 KB  Length: 296 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int main(){
    scanf("%d%d",&a,&b);
    printf("%d\n",gcd(a,b));
    return 0;
}