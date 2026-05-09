/*アルゴリズムと工夫点(Distribution/CPU: 55 ms Memory: 7052 KB  Length: 749 B)
i番目のすぬけ君が初めて宝石を貰うタイミングは，<i>高橋君からTi秒後に貰うか，<ii>i-1番目のすぬけ君から貰うかの2択．したがって，この二つの場合それぞれの最小の時間の内、最も小さい方が解となる．
そのため，まずTiの値が最小のi番目の人(i=iMin)が一番最初に宝石を貰うから，iMin+1番目の人の<ii>の場合の最小はmin(TiMin+SiMin,t[iMin+1])となる．この値を用いて，iMin+2番目以降も逐次的に求めていくことができる．
最悪計算量はO(N)<10^6 となり，十分高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

int n,s[MAX_N],t[MAX_N];
long long ans[MAX_N];

int main(){
    int i,j=0;
    long long now;
    scanf("%d",&n);
    rep(i,n)
        scanf("%d",&s[i]);
    rep(i,n){
        scanf("%d",&t[i]);
        if(t[j]>t[i])
            j=i;
    }
    i=(j+1)%n;
    now=t[j]+s[j];
    while(i!=j){
        if(now<t[i])
            ans[i]=now;
        else{
            ans[i]=t[i];
            now=t[i];
        }
        now+=s[i];
        i=(i+1)%n;
    }
    if(now<t[i])
        ans[i]=now;
    else{
        ans[i]=t[i];
        now=t[i];
    }
    rep(i,n)
        printf("%lld\n",ans[i]);
    return 0;
}