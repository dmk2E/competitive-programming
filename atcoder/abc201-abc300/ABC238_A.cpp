/*アルゴリズムと工夫点(Exponential or Quadratic/CPU: 1 ms Memory: 3876 KB  Length: 243 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    scanf("%d",&n);
    printf("%s\n",2<=n&&n<=4?"No":"Yes");
    return 0;
}