/*アルゴリズムと工夫点(Various Arrays（★5）/CPU: 28 ms Memory: 3868 KB  Length: 674 B)
i<jで，Aj>Ai(Ai,Aj)となる期待値の和=(転倒数の期待値)となることを利用する．
※期待値の線型性:「和の期待値は，期待値の和」となる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
vector<int> l,r;

int main(){
    int i,j,k,ii,jj,sum;
    double ans=0;
    scanf("%d",&n);
    l=vector<int>(n);
    r=vector<int>(n);
    rep(i,n)
        scanf("%d%d",&l[i],&r[i]);
    rep(i,n){
        for(j=i+1;j<n;j++){
            sum=0;
            for(ii=l[i];ii<=r[i];ii++){
                for(jj=l[j];jj<=r[j];jj++)sum+=jj<ii;
            }
            ans+=(double)sum/((r[i]-l[i]+1)*(r[j]-l[j]+1));
            //printf("(%d,%d):%f\n",i,j,ans);
        }
    }
    printf("%.8f\n",ans);
    return 0;
}