/*アルゴリズムと工夫点(Shiritori/CPU: 22 ms Memory: 8212 KB  Length: 829 B)
res(last,state):直前に選択したlast番目の文字列を選んでいて，今まで選んだ文字列の状態がstateである状態から始めたプレイヤーの勝敗
という，メモ化再帰で解ける．
最悪計算量は O(N^(2)*2^(N))≒10^7 となり，十分高速．
※初見6完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef enum state{
    WIN=1,
    LOSE=0,
    NIL=-1
}State;

int n;

int main(){
    int i;
    scanf("%d",&n);
    vector<string> s(n);
    rep(i,n)cin>>s[i];
    vector<vector<State> > memo(n+1,vector<State>(1<<n,NIL));
    auto res=[&](auto& f,int last,int state)->State{
        if(memo[last][state]!=NIL)return memo[last][state];
        int i;
        rep(i,n){
            if((state&(1<<i))==0&&(last==n||s[last].back()==s[i].front()))
                if(f(f,i,state|(1<<i))==LOSE)return memo[last][state]=WIN;
        }
        return memo[last][state]=LOSE;
    };
    printf("%s\n",res(res,n,0)==WIN?"First":"Second");
    //int j;rep(i,n+1)rep(j,1<<n){if(memo[i][j]!=NIL)printf("(%d,%d):%s\n",i,j,memo[i][j]==WIN?"WIN":"LOSE");}
    return 0;
}