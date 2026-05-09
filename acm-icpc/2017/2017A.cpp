/*アルゴリズムと工夫点(太郎君の買物/CPU: 0 ms Memory: 3464 KB  Length: 530 B)
2つの商品の選び方を全探索する．1テストケース当たり，O(N^(2))≒10^6 で十分高速．
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
    int i,j,ans;
    const int NIL=-1;
    while(1){
        scanf("%d%d",&n,&m);
        if(!(n||m))break;
        vector<int> a(n);
        ans=NIL;
        rep(i,n)scanf("%d",&a[i]);
        rep(i,n)rep(j,i)if(a[i]+a[j]<=m)ans=max(ans,a[i]+a[j]);
        if(ans==NIL)puts("NONE");
        else printf("%d\n",ans);
    }
    return 0;
}