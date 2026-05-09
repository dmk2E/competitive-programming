/*アルゴリズムと工夫点(Triple Attack/CPU: 59 ms Memory: 4928 KB  Length: 676 B)
現在の変数TとT以上の値T'が分かると，T~T'の変化で与えるダメージの値damageは，
three=(T~T'に含まれる3の倍数の個数)=T'/3-(T-1)/3 として，
damage=T'-T+1-three+3*three
と求めることができる．damageはT'の増加に対して単調増加するため，単調性があり，T'の値を二分探索で高速に求めることができる．
よって，各Hiに対して，T~T'の変化をO(log2(MAX))として求めることができるため，全体の最悪計算量はO(N*log2(MAX))<10^7 となり，高速．
※MAX=2*10^(5)*10^(9)+1<10^(15)とした
※Tが3進む度にdamage=5となるため，3つ分を一つとみなす公式解説のやり方はなるほどな～と思った．計算量はO(N)でより高速だし．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (long long)(1e15)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

ll search(ll h,ll t){
    ll left=t,right=MAX_N,mid,three;
    while(left<right){
        mid=(left+right)/2;
        three=mid/3-(t-1)/3;
        if(mid-t+1-three+three*3<h)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i;
    ll t=1;
    scanf("%d",&n);
    vector<ll> h(n);
    rep(i,n)scanf("%lld",&h[i]);
    rep(i,n)
        t=search(h[i],t)+1;
    printf("%lld\n",t-1);
    return 0;
}