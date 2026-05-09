/*アルゴリズムと工夫点(A Recursive Function/CPU: 1 ms Memory: 3852 KB  Length: 291 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int f(int k){
    if(k==0)return 1;
    return k*f(k-1);
}

int main(){
    scanf("%d",&n);
    printf("%d\n",f(n));
    return 0;
}