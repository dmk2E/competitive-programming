/*アルゴリズムと工夫点(Throwing the Die/CPU: 2 ms Memory: 3928 KB  Length: 381 B)
ゲーム系は後ろから考えることは定石だが，期待値が絡む場合，その期待値を元に次の行動を決める．
残りNターンある時のスコアの最大値f(N)とすると，f(N-1)の値を元にf(N)を求めることができる．
最悪計算量は O(N)<10^3 となり十分高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    double ans=0.0,now;
    rep(i,n){
        now=0.0;
        for(j=1;j<=6;j++)now+=max((double)j,ans);
        ans=now/6.0;
    }
    printf("%.7f\n",ans);
    return 0;
}