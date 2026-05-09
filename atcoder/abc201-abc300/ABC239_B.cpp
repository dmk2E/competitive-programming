/*アルゴリズムと工夫点(Integer Division/CPU: 1 ms Memory: 3896 KB  Length: 243 B)
pythonでは，符号にかかわらず，商で床関数の機能を果たす．
しかし，C++では，符号にかかわらず10進数表記での，小数点以下切り捨てが行われるため，符号により床関数の書き方が異なる．
※https://atcoder.jp/contests/abc239/editorial/3390
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll x;

int main(){
    scanf("%lld",&x);
    printf("%lld\n",x>=0?x/10:(x-9)/10);
    return 0;
}