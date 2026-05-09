/*アルゴリズムと工夫点(Exchange Game/CPU: 38 ms Memory: 69140 KB  Length: 1139 B)
ゲームの状態表現が難しいゲーム問題．
カードを場に捨てた時，カードを新たに拾える場合と拾えない場合の2パターンあることに注意．
※持っている手札の状態の表現方法として，「各プレイヤーがどのカードを持っているか」という見方．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_NML 12
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

enum State{
    NIL=0,
    LOSE=1,
    WIN=2,
};

int n,m,l;

int main(){
    int i,j,state;
    scanf("%d%d%d",&n,&m,&l);
    vector<int> card(n+m+l);
    rep(i,n+m+l)scanf("%d",&card[i]);
    vector<vector<State> > memo(1<<(n+m+l),vector<State>(1<<(n+m+l),NIL));
    auto rec=[&](auto& f,int t,int a)->State{
        if(memo[t][a]!=NIL)return memo[t][a];
        int i,j,tt,c;
        c=((1<<(n+m+l))-1)^(t^a);
        rep(i,n+m+l){
            if((t>>i)&1){
                tt=t^(1<<i);
                //新たにカードを拾うパターン
                rep(j,n+m+l)if(((c>>j)&1)&&card[j]<card[i]&&f(f,a,tt|(1<<j))==LOSE)return memo[t][a]=WIN;
                //新たに拾えないパターン
                if(f(f,a,tt)==LOSE)return memo[t][a]=WIN;
            }
        }
        return memo[t][a]=LOSE;
    };
    printf("%s\n",rec(rec,(1<<n)-1,((1<<(n+m))-1)^((1<<n)-1))==WIN?"Takahashi":"Aoki");
    return 0;
}