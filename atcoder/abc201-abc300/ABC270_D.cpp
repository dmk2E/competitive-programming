/*アルゴリズムと工夫点(Stones/CPU: 119 ms Memory: 8464 KB  Length: 829 B)
f(n,i):残りの山の石の数がn個の状態で，先手がAi個取り除いてゲームを始めた時，先手が取り除くことができる最大の石の数
とするメモ化再帰で解ける．
最悪計算量は O(N*K)<10^7 となり十分高速．
※初見時間内4完!
※状態として，実はどの操作を選んだかは保持しなくてよい．なぜならば，遷移先の状態における値を求めるのに，前の人がどの操作を選んだかという情報はいらないからだ．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j,ans;
    scanf("%d%d",&n,&k);
    vector<int> a(k);
    rep(i,k)scanf("%d",&a[i]);
    const int NIL=-1;
    vector<vector<int> > memo(n+1,vector<int>(k,NIL));
    ans=NIL;
    auto rec=[&](auto &f,int nn,int kk)->int{
        if(nn==0)return 0;
        int i,j,mmax=0;
        rep(i,k){
            if(nn-a[kk]<a[i])break;
            mmax=max(mmax,memo[nn-a[kk]][i]==NIL?memo[nn-a[kk]][i]=f(f,nn-a[kk],i):memo[nn-a[kk]][i]);
        }
        //printf("rec(%d,%d)=%d\n",nn,kk,nn-mmax);
        return memo[nn][kk]=nn-mmax;
    };
    rep(i,k)if((j=rec(rec,n,i))>ans)ans=j;
    printf("%d\n",ans);
    return 0;
}