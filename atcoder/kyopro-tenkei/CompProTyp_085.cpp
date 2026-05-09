/*アルゴリズムと工夫点(Multiplication 085（★4）/CPU: 427 ms Memory: 3884 KB  Length: 349 B)
ABC226_Cと似たような問題だった．
調和級数より最悪計算量は，O(√K+√(k/2)+√(k/3)+...+√(K/K^(1/3)))<O(√K+√k/2+√k/3+...+√K/K^(1/3))<O(√K*log(K^(1/3)))≒10^7 となり，高速．
※キーワードは約数の個数は少ない
※工夫した全探索/約数列挙の復習
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll k;

int main(){
    int i,j;
    ll ans=0;
    scanf("%lld",&k);
    for(i=1;(ll)i*i*i<=k;i++)
        for(j=i;(ll)i*j*j<=k;j++)if(k%((ll)i*j)==0)ans++;
    printf("%lld\n",ans);
    return 0;
}