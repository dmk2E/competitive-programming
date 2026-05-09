/*アルゴリズムと工夫点(/CPU: 61 ms Memory: 14052 KB  Length: 725 B)
数え上げの主客転倒の問題．
固定する条件を「区間の端」とするのではなく，「要素の値」とし，その値を含む区間の総数を数え上げていくことで求まる．
要素の値毎に，配列上の添え字を昇順に保持して置くことで，高速に数え上げることができる．数え上げは余事象の数え上げを用いて簡単に求めるようにする．
最悪計算量はO(N+max(Ai))<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,now;
    ll ans=0,tmp;
    scanf("%d",&n);
    vector<vector<int> > a2Id(n+1,vector<int>(0));
    rep(i,n){
        scanf("%d",&j);
        a2Id[j].push_back(i);
    }
    rep(i,n+1){
        now=tmp=0;
        rep(j,a2Id[i].size()){
            tmp+=((ll)a2Id[i][j]-now)*(a2Id[i][j]-now-1)/2+a2Id[i][j]-now;
            now=a2Id[i][j]+1;
        }
        tmp+=((ll)n-now)*(n-now-1)/2+n-now;
        if((int)a2Id[i].size()>0)
            ans+=(ll)n*(n-1)/2+n-tmp;
    }
    printf("%lld\n",ans);
    return 0;
}