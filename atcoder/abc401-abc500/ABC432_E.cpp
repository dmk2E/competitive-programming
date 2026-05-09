/*アルゴリズムと工夫点(Clamp/CPU: 171 ms Memory: 13600 KB  Length: 2740 B)
BIT で解く．
値毎の数と，値毎の総和（値*数）を配列で保持し，高速に加算&総和計算を多なうことで解ける．
最悪計算量は，O((N + Q) * log2(MAX_A)) < 10^8 となり間に合う．
※ 値そのものを添え字とし，値に関係する何らかの値を保持する配列において，1要素の加算，範囲総和を高速に求める場合，BITが有効．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A (int)((5e5) + 1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class BinaryIndexedTree{
    ll MOD=(1e18);
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
        assert(1<=l&&l<bit.size());
        assert(1<=r&&r<bit.size());
        assert(l<=r);
        return (MOD+sum(r)-sum(l-1))%MOD;
    }

    int size(){
        return (int)bit.size();
    }

    int lowerBound(ll sum_val){
        int left=0,right=this->size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(this->sum(mid)<sum_val)left=mid+1;
            else right=mid;
        }
        return left;
    }

    int upperBound(ll sum_val){
        int left=0,right=this->size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(this->sum(mid)<=sum_val)left=mid+1;
            else right=mid;
        }
        return left;
    }

    void show(){
        int i;
        rep(i,bit.size()-2)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    BIT tree_for_sum(MAX_A + 1),tree_for_cnt(MAX_A + 1);
    vector<int> a(n);
    rep(i,n){
        scanf("%d",&a[i]);
        tree_for_sum.add(a[i] + 1, a[i]);
        tree_for_cnt.add(a[i] + 1, 1);
    }
    while(q--){
        scanf("%d",&i);
        if(i == 1){
            int x,y;
            scanf("%d%d",&x,&y);
            tree_for_sum.add(a[x - 1] + 1, -a[x - 1]);
            tree_for_cnt.add(a[x - 1] + 1, -1);
            a[x - 1] = y;
            tree_for_cnt.add(y + 1, 1);
            tree_for_sum.add(y + 1, y);
        }else{
            int l,r;
            scanf("%d%d",&l,&r);
            if(l < r){
                printf("%lld\n", l * tree_for_cnt.sum(l + 1) + 
                                 r * tree_for_cnt.ssum(r + 1, MAX_A + 1) + 
                                 (l + 1 == r ? 0 : tree_for_sum.ssum(l + 2, r))
                );
            }else printf("%lld\n", (ll)l * n);
        }
    }
    return 0;
}