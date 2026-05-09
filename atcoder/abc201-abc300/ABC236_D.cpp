/*アルゴリズムと工夫点(Dance/CPU: 47 ms Memory: 3940 KB  Length: 1168 B)
N<=8 と小さいから，2人組の分かれ方を全探索する．
実装は再帰で行うが，同じ分かれ方が生成されないよう，枝刈りを上手く行うこと．
最悪計算量は O((2*n-1)*(2*n-3)*...*1*(2*n))<10^8 となり間に合う．
※初見4完!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    const ll NIL=-1;
    vector<vector<ll> > a(2*n,vector<ll>(2*n,NIL));
    rep(i,2*n-1){
        for(j=i+1;j<2*n;j++){
            scanf("%lld",&a[i][j]);
            a[j][i]=a[i][j];
        }
    }
    vector<int> p(2*n,NIL);
    auto rec=[&](auto& f,int n,ll sum)->ll{//あとn組決める
        if(n==0){
            //int i;rep(i,p.size())printf("%d ",p[i]);puts("");
            return sum;
        }
        int i,j;
        ll mx=NIL;
        rep(i,p.size()){
            if(p[i]==NIL){
                p[i]=n;
                for(j=i+1;j<(int)p.size();j++){
                    if(p[j]==NIL){
                        p[j]=n;
                        mx=max(mx,f(f,n-1,sum^a[i][j]));
                        p[j]=NIL;
                    }
                }
                p[i]=NIL;
                break;
            }
        }
        return mx;
    };
    printf("%lld\n",rec(rec,n,0));
    return 0;
}