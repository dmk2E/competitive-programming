/*アルゴリズムと工夫点(AND and SUM/CPU: 56 ms Memory: 3792 KB  Length: 540 B)
ビット毎に着目して考察すると，aのiビット目が「1」の時，x,yのiビット目も共に「1」になる．
それ以外のビットでは，x,yのどちらか一方のみが「1」か両方とも「0」となる．
よって，まず必ずx+y>=2*a となる．
sum=2*aの状態から初めて，2^60の位から見ていき，その位の値を加算してもsumの値がsを超えなければ加算していく(x,yのどちらかのその桁を「1」にして)．
その結果，sum==s となれば"Yes" となる．
最悪計算量は O(MAX*T)<10^7 となり高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;
ll a,s;

int main(){
    int i,j;
    ll sum;
    scanf("%d",&t);
    const int MAX=60;
    while(t--){
        scanf("%lld%lld",&a,&s);
        sum=a*2;
        j=MAX;
        while(j>=0){    
            if(!((a>>j)&1)&&((ll)1<<j)+sum<=s)
                sum+=((ll)1<<j);
            j--;
        }
        printf("%s\n",(j==-1&&sum==s)?"Yes":"No");
    }
    return 0;
}