/*アルゴリズムと工夫点(Distance Sequence/CPU:  ms Memory:  KB  Length:  B)
動的計画法で解く．区間和を高速に求めるためにBITを用いる．O(N*M*log2(N))<10^8 で間に合う．
※公式解説にある通り，累積和を事前に求めておけばより早い．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class BinaryIndexedTree{
    vector<ll> bit;
public:
    BinaryIndexedTree(int n=0){
        bit=vector<ll>(n+1,0);
    }

    void init(int n){
        bit=vector<ll>(n+1,0);
    }

    void add(int k,long long dx){
        assert(1<=k&&k<(int)bit.size());
        while(k<=bit.size()){
            bit[k]=(bit[k]+dx)%MOD;
            k+=(k&(-k));
        }
    }

    ll sum(int k)const{
        ll s=0;
        while(k>0){
            s=(s+bit[k])%MOD;
            k-=(k&(-k));
        }
        return s;
    }

    ll ssum(int l,int r){
        if(l>=r)return 0;
        return (MOD+sum(r-1)-sum(l-1))%MOD;
    }

    int size(){
        return (int)bit.size();
    }

    void show(){
        int i;
        rep(i,bit.size()-2)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

int n,m,k;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&m,&k);
    BIT dp(m);
    rep(i,m)dp.add(i+1,1);
    rep(i,n-1){
        BIT now(m);
        if(k==0) rep(j,m)now.add(j+1,dp.sum(m));
        else rep(j,m)now.add(j+1,(dp.ssum(1,j+1-k+1)+dp.ssum(j+1+k,m+1))%MOD);
        swap(dp,now);
    }
    printf("%lld\n",dp.sum(m));
    return 0;
}