/*アルゴリズムと工夫点(Polynomial division/CPU: 1 ms Memory: 3872 KB  Length: 563 B)
多項式の割り算をイメージして，次数の高い項の係数から順に決定していく．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    ll sum;
    scanf("%d%d",&n,&m);
    vector<int> a(n+1),c(n+m+1);
    vector<ll> b(m+1,0);
    rep(i,n+1)scanf("%d",&a[i]);
    rep(i,n+m+1)scanf("%d",&c[i]);
    for(i=m;i>=0;i--){
        b[i]=c[n+i]/a[n];
        for(j=n;j>=0;j--)c[i+j]-=a[j]*b[i];
    }
    rep(i,m)printf("%lld ",b[i]);printf("%lld\n",b[i]);
    return 0;
}