/*アルゴリズムと工夫点(Triangle?/CPU: 7 ms Memory: 3880 KB  Length: 538 B)
3つの頂点が定まれば，3つの点が同一直線状に無ければその3点を結んでできる図形は三角形になる．
この「3つの点a,b,cが同一直線状にないか」の判定は「2つのベクトル(b-a)と(c-a)の外積が0でないか」で，O(1)で判定可能．
3つの頂点の組み合わせの列挙にO(N^3)かかるため，最悪計算量はO(N^3)<10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,k,ans=0;
    ll x1,y1,x2,y2;
    scanf("%d",&n);
    vector<int> x(n),y(n);
    rep(i,n)
        scanf("%d%d",&x[i],&y[i]);
    rep(i,n)rep(j,i){
        x1=x[j]-x[i];y1=y[j]-y[i];
        rep(k,j){
            x2=x[k]-x[i];y2=y[k]-y[i];
            if(x1*y2-y1*x2!=0)ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}