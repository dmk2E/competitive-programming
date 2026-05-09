/*アルゴリズムと工夫点(Edge Checker/CPU: 1 ms Memory: 3912 KB  Length: 285 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b;

int main(){
    scanf("%d%d",&a,&b);
    a--;b--;
    printf("%s\n",((a-1+10)%10==b||(a+1)%10==b)?"Yes":"No");
    return 0;
}