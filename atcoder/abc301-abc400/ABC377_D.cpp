/*アルゴリズムと工夫点(Many Segments 2/CPU: 48 ms Memory: 4972 KB  Length: 716 B)
lの値を固定した時，条件を満たす[l,r]の個数を数えることを考える．
区間[l,r]がある区間[L,R]を完全に含むとは，次の条件を満たす．
・l<=L
・R<=r
二つの条件を同時に考えるのは難しいので，平面走査を行う．
l=M,M-1,...,1の順で数え上げていくが，l=kの時の個数を数える際，[k,Ri]となる全ての区間を見て，[k,Ri](l<=k<=M)におけるRiの最小値minRを更新する．
そうすると，上記の条件を満たさないRiの総数は，''minR-l''となる．これの総和を求めればよい．
最悪計算量は O(N*log2(N)+M)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;//(L,R)

int n,m;

int main(){
    int i,j,minR;
    ll ans=0;
    scanf("%d%d",&n,&m);
    vector<P> ipt(n);
    rep(i,n){
        scanf("%d%d",&ipt[i].first,&ipt[i].second);
    }
    sort(ipt.begin(),ipt.end());
    minR=m+1;
    for(i=m,j=n-1;i>=1;i--){
        while(j>=0&&ipt[j].first==i){
            minR=min(ipt[j].second,minR);
            j--;
        }
        ans+=max(0,minR-i);
        //printf("minR:%d ans:%lld\n",minR,ans);
    }
    printf("%lld\n",ans);
    return 0;
}