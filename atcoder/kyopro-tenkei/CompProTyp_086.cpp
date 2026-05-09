/*アルゴリズムと工夫点(Snuke's Favorite Arrays（★5）/CPU: 14 ms Memory: 3904 KB  Length: 1167 B)
ビット演算が題材の問題であるため，まずビット毎に分けて考える．
・A[x]&A[y]&A[z]==w を満たすということは，wのビットが「0」となる桁は必ず，A[x],A[y],A[z]の桁においても「0」である必要がある．
・A[x]&A[y]&A[z]==w を満たすということは，wのビットが「1」となる桁は必ず，A[x],A[y],A[z]の桁のどれかにおいて「1」である必要がある．
※bitごとに独立に考える&ビット全探索
※初見AC出来た．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX 60
#define MOD (int)((1e9)+7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j,cnt,tmp;
    ll ans;
    scanf("%d%d",&n,&q);
    vector<int> x(q),y(q),z(q);
    vector<ll> w(q);
    vector<ll> bit(n,0);//各桁が0と確定した場合，「true」と返す．
    rep(j,q){
        scanf("%d%d%d%lld",&x[j],&y[j],&z[j],&w[j]);
        x[j]--;y[j]--;z[j]--;
        rep(i,MAX)if((w[j]&((ll)1<<i))==0){
            bit[x[j]]|=((ll)1<<i);
            bit[y[j]]|=((ll)1<<i);
            bit[z[j]]|=((ll)1<<i);
        }
    }
    auto judge=[&](int state,int num)->bool{
        int i;
        rep(i,q)if(((w[i]&(1LL<<num))>0)&&(state&(1<<x[i]))==0&&(state&(1<<y[i]))==0&&(state&(1<<z[i]))==0)return false;
        return true;
    };
    ans=1;
    rep(j,MAX){
        tmp=cnt=0;
        rep(i,n)if(bit[i]&(1LL<<j))tmp|=(1<<i);
        rep(i,1<<n){
            if((tmp&i)==0)cnt+=judge(i,j);
        }
        ans=(ans*cnt)%MOD;
    }
    printf("%lld\n",ans);
    return 0;
}