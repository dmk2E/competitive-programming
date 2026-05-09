/*アルゴリズムと工夫点(Sleep Log/CPU: 230 ms Memory: 17500 KB  Length: 1902 B)
クエリ先読み+座圧+累積和 で解く．
クエリで指定される整数の組 (l,r) と配列Aの値のみに，時間の値について座圧して累積和を取る．
（累積和：sum[i]_i分後ちょうどの時の、累積睡眠時間）
最悪計算量は，O(N+Q*log2(3*N+Q))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
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

int n,q;
const int MAX_A=(int)(1e9);

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n);
    CC as;
    as.add(MAX_A+1);
    rep(i,n){
        scanf("%d",&a[i]);
        as.add(max(0,a[i]-1));
        as.add(a[i]);
        as.add(a[i]+1);
    }
    scanf("%d",&q);
    vector<int> l(q),r(q);
    rep(i,q){
        scanf("%d%d",&l[i],&r[i]);
        as.add(l[i]);
        as.add(r[i]);
    }
    vector<ll> sum_a(as.size()+1,0);
    for(i=1;i<n;i+=2){
        int start=as(a[i]),end=as(a[i+1]);
        for(j=start+1;j<=end;j++)sum_a[j]=as[j]-as[j-1];
    }
    // rep(i,as.size())printf("%d:%lld\n",as[i],sum_a[i]);
    rep(i,as.size())sum_a[i+1]+=sum_a[i];
    rep(i,q)printf("%lld\n",sum_a[as(r[i])]-sum_a[as(l[i])]);
    return 0;
}