/*アルゴリズムと工夫点(Equilateral Triangle/CPU: 30 ms Memory: 5656 KB  Length: 680 B)
円周上の座標毎の個数を管理し，数え上げる．
円周上で作成可能な正三角形の長さは，一意に定まることに気づけるかが肝となる．
最悪計算量は，O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,l;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d",&n,&l);
    if(l%3>0){
        puts("0");
        return 0;
    }
    vector<int> id_to_coord(n,0),coord_to_cnt(l,0);
    coord_to_cnt[0]=1;
    rep(i,n-1){
        scanf("%d",&j);
        id_to_coord[i+1]=(id_to_coord[i]+j)%l;
        coord_to_cnt[id_to_coord[i+1]]++;
    }
    j=l/3;
    rep(i,j)ans+=((ll)coord_to_cnt[i])*coord_to_cnt[(i+j)%l]*coord_to_cnt[(i-j+l)%l];
    printf("%lld\n",ans);
    return 0;
}