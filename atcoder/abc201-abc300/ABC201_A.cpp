/*アルゴリズムと工夫点(Tiny Arithmetic Sequence/CPU: 5 ms Memory: 3872 KB  Length: 266 B)
a1,a2,a3 がこの順に等差数列である時、等差中項の公式「2*a2=a1+a3」(高校数学B)が成立することを利用する。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int a1,a2,a3;

int main(){
    scanf("%d%d%d",&a1,&a2,&a3);
    if((2*a1==a2+a3||2*a2==a1+a3||2*a3==a1+a2))
        puts("Yes");
    else
        puts("No");
    return 0;
}