/*アルゴリズムと工夫点(Cuboid Sum Query/CPU: 162 ms Memory: 7840 KB  Length: 1025 B)
Nが最大100なので，xの各値毎に，yz平面の2次元累積和Sumをとっておき，クエリの度に指定された範囲のxそれぞれについて，Sumを用いて指定された範囲のy,zの範囲の部分和をO(1)で出す．最悪計算量はO(N^2+N*Q)≒10^7 となり，高速．
※3次元累積和が存在するとは.....知らなかった．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q,sum[MAX_N][MAX_N+1][MAX_N+1]={0},a,lx,rx,ly,ry,lz,rz;

int main(){
    int i,j,k;
    ll ans=0;
    scanf("%d",&n);
    rep(i,n){
        rep(j,n){
            rep(k,n){
                scanf("%d",&a);
                sum[i][j+1][k+1]=a+sum[i][j][k+1]+sum[i][j+1][k]-sum[i][j][k];
            }
        }
    }
    //rep(i,n){rep(j,n+1){rep(k,n+1){printf("%d ",sum[i][j][k]);}puts("");}puts("");puts("");}
    scanf("%d",&q);
    while(q--){
        ans=0;
        scanf("%d%d%d%d%d%d",&lx,&rx,&ly,&ry,&lz,&rz);
        lx--;ly--;lz--;
        for(;lx<rx;lx++){
            ans+=(ll)sum[lx][ry][rz]-sum[lx][ry][lz]-sum[lx][ly][rz]+sum[lx][ly][lz];
        }
        printf("%lld\n",ans);
    }
    return 0;
}