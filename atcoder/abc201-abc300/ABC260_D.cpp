/*アルゴリズムと工夫点(Draw Your Cards/CPU: 297 ms Memory: 8124 KB  Length: 2901 B)
場に存在するカードの中で，X以上で最小の整数の探索を二分探索を用いるが，整列の為Nターン毎回ソートするとTLEしてしまう．
そこで，BITを用いた並列二分探索により，高速な探索を実現する．
また，重ねられたの集合はUnion-Find木で処理し，代表となる頂点が，その集合が何ターン目に食べられたかを把握すればよい．
最悪計算量は O(N*(log2(N))^2)<10^8 となり間に合う．
※バーチャルコンテスト内初見4完
※解説では...毎回整列済みの状態で，高速な探索&値追加&値削除 が行える，setを用いた方が高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par,cnt;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        cnt=vector<int>(n,1);
        int i;
        rep(i,n)
            par.push_back(i);
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return ;
        if(rank[y]<rank[x]){
            par[y]=x;
            cnt[x]+=cnt[y];
        }else{
            par[x]=y;
            cnt[y]+=cnt[x];
            if(rank[y]==rank[x])rank[y]++;
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    int count(int x){
        return cnt[root(x)];
    }

    void show(){
        int i;
        printf("par:");rep(i,rank.size())printf("%d ",par[i]);puts("");
        printf("cnt:");rep(i,rank.size())printf("%d ",cnt[root(i)]);puts("");
    }
}UF;

typedef class BinaryIndexedTree{
    int MOD=998244353;
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

    void show(){
        int i;
        rep(i,bit.size()-2)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

int n,k,p;

int main(){
    int i,j,left,right,mid;
    scanf("%d%d",&n,&k);
    const int NIL=-1;
    vector<int> ans(n+1,NIL);
    UF tree(n+1);
    BIT field(n);
    rep(i,n){
        scanf("%d",&p);
        left=p;
        right=n+1;
        while(left<right){
            mid=(left+right)/2;
            if(field.ssum(p,mid)<=0)left=mid+1;
            else right=mid;
        }
        //printf("turn:%d left:%d\n",i+1,left);
        if(left<=n){
            field.add(left,-1);
            field.add(p,1);
            tree.unite(left,p);
        }else
            field.add(p,1);
        if(tree.count(p)==k)field.add(p,-1),ans[tree.root(p)]=i+1;
    }
    rep(i,n)printf("%d\n",ans[tree.root(i+1)]);
    return 0;
}