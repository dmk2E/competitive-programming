/*アルゴリズムと工夫点(池のある庭園/CPU: 0 ms Memory: 3492 KB  Length: 1243 B)
長方形の始点と，幅と奥行きの長さを固定して，全探索する．
最悪計算量は O((h*w)^(3))≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_E 9
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int d,w;

int main(){
    int i,j,k,ii,jj,ans;
    const int NIL=0;
    while(1){
        scanf("%d%d",&d,&w);
        if(!(d||w))break;
        ans=NIL;
        vector<vector<int> > e(d,vector<int>(w,0));
        auto calcCap=[&](int sy,int sx,int h,int w)->int{
            int i,j,min_e=MAX_E+1,ans=0;
            rep(j,w)min_e=min(min_e,e[sy][sx+j]);
            rep(j,w)min_e=min(min_e,e[sy+h-1][sx+j]);
            rep(i,h)min_e=min(min_e,e[i+sy][sx]);
            rep(i,h)min_e=min(min_e,e[i+sy][sx+w-1]); 
            rep(i,h-2)rep(j,w-2){
                if(min_e<=e[sy+i+1][sx+j+1])return NIL;
                ans+=min_e-e[sy+i+1][sx+j+1];
            }
            return ans;
        };
        rep(i,d)rep(j,w)scanf("%d",&e[i][j]);
        rep(i,d)rep(j,w){
            for(ii=3;ii<=d;ii++){
                if(i+ii>d)break;
                for(jj=3;jj<=w;jj++){
                    if(j+jj>w)break;
                    ans=max(ans,calcCap(i,j,ii,jj));
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}