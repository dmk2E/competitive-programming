/*アルゴリズムと工夫点(Best Performances/CPU: 729 ms Memory: 20200 KB  Length: 4675 B)
クエリ先読み+並列二分探索（座標圧縮+BIT）で解く．
配列Aの中で，上位k個の値の総和を各クエリ毎に求めればよい．
以下の操作を高速に行うことを考える．
・値の重複を考慮した集合（set）で，要素の削除と挿入
・昇順/降順に，前からi番目の要素
これは，値毎の個数を保持した配列上で並列二分探索を行うことで実現できる．
ただし，値が大きいため，クエリ先読み+座圧で対応．

すると，上位k個の要素の中の最小値を高速に求めることができ，この値をthreshとする．
BITに対する操作は，a[x]とyの値それぞれが，thresh未満であるか否かの4通りに分けられ，それぞれで処理をすればよい．
最悪計算量は O(N+Q*log2(N)*log2(N))<10^8 となり間に合う．
※公式解説ではmultiset を2つ併用して解いていた
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MIN_Y 0
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class CoordinatedCompression{
    bool initiated;
    vector<int> xs;
public:
    CoordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(int x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(int k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    int operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
}CC;

typedef class BinaryIndexedTree{
    int MOD=998244353;
    vector<ll> bit;
public:
    /// @brief BITのコンストラクタ
    /// @param n 要素数
    BinaryIndexedTree(int n=0){
        bit=vector<ll>(n+1,0);
    }

    /// @brief 初期化用
    /// @param n 要素数
    void init(int n){
        bit=vector<ll>(n+1,0);
    }

    /// @brief 一つの要素への加算処理
    /// @param k 1-indexed で添え字指定(0を指定してはダメ)
    /// @param dx 加算する値
    void add(int k,long long dx){//k=0を代入してはダメ
        assert(1<=k&&k<(int)bit.size());
        while(k<=bit.size()){
            bit[k]=(bit[k]+dx)%MOD;
            k+=(k&(-k));
        }
    }

    /// @brief bit[1,k]の合計値を得る
    /// @param k 
    /// @return bit[1,k]の合計値
    ll sum(int k)const{
        ll s=0;
        while(k>0){
            s=(s+bit[k])%MOD;
            k-=(k&(-k));
        }
        return s;
    }

    /// @brief bit[l,r]の合計値
    /// @param l 閉区間の左端
    /// @param r 閉区間の右端
    /// @return 閉区間の合計値
    ll ssum(int l,int r){
        assert(1<=l&&l<bit.size());
        assert(1<=r&&r<bit.size());
        assert(l<=r);
        return (MOD+sum(r)-sum(l-1))%MOD;
    }

    /// @brief BITのサイズ
    /// @return BITの要素数
    int size(){
        return (int)bit.size();
    }

    /// @brief 並列二分探索で，閾値以上となる添え字探索
    /// @param sum_val 閾値
    /// @return 添え字
    int lowerBound(ll sum_val){
        int left=0,right=this->size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(this->sum(mid)<sum_val)left=mid+1;
            else right=mid;
        }
        return left;
    }

    /// @brief 並列二分探索で，閾値より大きくなる添え字探索
    /// @param sum_val 閾値
    /// @return 添え字
    int upperBound(ll sum_val){
        int left=0,right=this->size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(this->sum(mid)<=sum_val)left=mid+1;
            else right=mid;
        }
        return left;
    }

    /// @brief BITの中身を表示する
    void show(){
        int i;
        rep(i,bit.size()-2)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

int n,k,q;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d%d",&n,&k,&q);
    vector<int> x(q),y(q),a(n+1,MIN_Y);
    CC as;as.add(MIN_Y-1);as.add(0);
    rep(i,q){
        scanf("%d%d",&x[i],&y[i]);
        as.add(y[i]);
    }
    BIT tree(as.size());
    tree.add(as(0),n);
    rep(i,q){
        int lb=tree.lowerBound(n-k+1);
        if(a[x[i]]<as[lb]&&y[i]<as[lb]){
            tree.add(as(a[x[i]]),-1);
            tree.add(as(y[i]),1);
        }else if(a[x[i]]>=as[lb]&&y[i]<as[lb]){
            ans-=a[x[i]];
            tree.add(as(a[x[i]]),-1);
            tree.add(as(y[i]),1);
            ans+=as[tree.lowerBound(n-k+1)];
        }else if(a[x[i]]<as[lb]&&y[i]>=as[lb]){
            ans-=as[lb];
            ans+=y[i];
            tree.add(as(a[x[i]]),-1);
            tree.add(as(y[i]),1);
        }else{
            ans-=a[x[i]];
            ans+=y[i];
            tree.add(as(a[x[i]]),-1);
            tree.add(as(y[i]),1);
        }
        a[x[i]]=y[i];
        printf("%lld\n",ans);
    }
    return 0;
}