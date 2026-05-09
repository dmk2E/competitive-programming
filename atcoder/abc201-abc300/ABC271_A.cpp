/*アルゴリズムと工夫点(484558/CPU: 1 ms Memory: 3880 KB  Length: 298 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string alfa="0123456789ABCDEF";

int main(){
    string ans="";
    scanf("%d",&n);
    printf("%c%c\n",alfa[n/16],alfa[n%16]);
    return 0;
}