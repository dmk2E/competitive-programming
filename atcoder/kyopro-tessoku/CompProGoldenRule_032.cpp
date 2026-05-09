/*アルゴリズムと工夫点(A32 - Game 1/CPU: 2 ms Memory: 5292 KB  Length: 630 B)
最適な戦略を，その状態から選択できる操作全てを試した勝敗結果から求める「ゲーム木探索」，つまりメモ化再帰で解く．
状態は 0~NのN+1個しかなく，各状態は最大でも2回しか巡回しないから，最悪計算量は O(N)≒10^5 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

enum State{
    NIL=-1,
    LOSE=0,
    WIN=1
};

int n,a,b;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&a,&b);
    vector<char> memo(n+1,NIL);
    auto rec=[&](auto& f,int n)->bool{
        if(n-a>=0&&((memo[n-a]==NIL?f(f,n-a):memo[n-a])==LOSE))return memo[n]=WIN;
        if(n-b>=0&&((memo[n-b]==NIL?f(f,n-b):memo[n-b])==LOSE))return memo[n]=WIN;
        return memo[n]=LOSE;
    };
    printf("%s\n",rec(rec,n)?"First":"Second");
    return 0;
}