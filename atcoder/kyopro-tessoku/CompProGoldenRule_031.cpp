/*アルゴリズムと工夫点(Divisors/CPU: 2 ms Memory: 3916 KB  Length: 307 B)
包除原理を用いれば，O(1)で求まる．3,5->(a,b)の場合，O(log(max(a,b))) で求められる．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

ll gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int main(){
    scanf("%lld",&n);
    printf("%lld\n",n/3+n/5-n/(3*5/gcd(3,5)));
    return 0;
}