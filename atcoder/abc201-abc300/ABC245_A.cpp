/*アルゴリズムと工夫点(Good morning/CPU: 1 ms Memory: 3728 KB  Length: 302 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,d;

int main(){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    printf("%s\n",(a<c||(a==c&&b<=d))?"Takahashi":"Aoki");
    return 0;
}