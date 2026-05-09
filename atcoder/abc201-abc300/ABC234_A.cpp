/*アルゴリズムと工夫点(Weird Function/CPU: 1 ms Memory: 3824 KB  Length: 285 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

int f(int t){
    return t*t+2*t+3;
}

int main(){
    scanf("%d",&t);
    printf("%d\n",f(f(f(t)+t)+f(f(t))));
    return 0;
}