/*アルゴリズムと工夫点(Lucky Numbers/CPU: 791 ms Memory: 66384 KB  Length: 630 B)
考察
・A0の値を決め打ったら，全てのA0が決まる
・M<=10
・A0の値を1増やすと，他のAiの値は1だけ増減する（実験で分かった）
-> 単調減少する方と単調増加する方で要素を分けて考えると，相互関係は変化なし？
全ての項について，A0の一次式（a+c*A0）で表せる．
よって，AiがXのいずれかになる時の，A0の値を記録していくのが良い．
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,ans=0,c;
    ll a;
    scanf("%d%d",&n,&m);
    vector<int> s(n-1),x(m);
    rep(i,n-1)scanf("%d",&s[i]);
    rep(i,m)scanf("%d",&x[i]);
    map<ll,int> a0_to_cnt;
    a=0;c=1;
    rep(i,n){
        rep(j,m)a0_to_cnt[(x[j]-a)/c]++;
        if(i==n-1)break;
        a=s[i]-a;
        c=-c;
    }
    for(auto x:a0_to_cnt)ans=max(ans,x.second);
    printf("%d\n",ans);
    return 0;
}