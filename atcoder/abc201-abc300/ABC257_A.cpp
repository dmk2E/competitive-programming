/*アルゴリズムと工夫点(A to Z String 2/CPU: 1 ms Memory: 3868 KB  Length: 269 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x;

int main(){
    scanf("%d%d",&n,&x);
    x--;
    printf("%c\n",(x/n)+'A');
    return 0;
}