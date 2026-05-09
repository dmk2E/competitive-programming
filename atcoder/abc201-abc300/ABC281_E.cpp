/*アルゴリズムと工夫点(Least Elements/CPU: 258 ms Memory: 19292 KB  Length: 3366 B)
座標圧縮+BIT+二分探索 で解ける．
a[i,i+M-1]において，存在する整数1~Nそれぞれの個数を一次元配列で持ったものの，累積和cntを持っておく．cntを用いると，存在する整数1~Xそれぞれの個数の総和がk個以上になるXは二分探索で求めることができる．
また別に，整数[1,X]の範囲で，a[i,i+M-1]において存在する整数の和sumを保持しておくと，a[i,i+M-1]の先頭k個の和はsum[X+1]-X*(cnt[X+1]-k) となる．
ただし，高速で値更新をする必要があるため，cnt,sumはそれぞれBITで保持して置く．また，Aiの値が10^9と大きいため，座標圧縮を行う．
全体の最悪計算量は O((N-M+1)*log2(N))<10^7 となり，高速．
※初!初見5完達成!嬉しい!
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class CoordinateCompression{
    int MIN_X,MAX_X;
    bool initialized;
    vector<int> xs;
public:
    CoordinateCompression(int mmin=0,int mmax=(int)(1e9)+1):MIN_X(mmin),MAX_X(mmax),initialized(false){}
    
    void add(int x){
        if(MIN_X<=x-1&&x-1<=MAX_X)
            xs.push_back(x-1);
        if(MIN_X<=x&&x<=MAX_X)
            xs.push_back(x);
        if(MIN_X<=x+1&&x+1<=MAX_X)
            xs.push_back(x+1);
        initialized=false;
    }

    void init(){
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
        initialized=true;
    }

    int x2Id(int x){
        if(!initialized)init();
        int left=0,right=xs.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(xs[mid]<x)
                left=mid+1;
            else
                right=mid;
        }
        return left;
    }

    int id2X(int id){
        if(!initialized)init();
        return xs[id];
    }

    int operator()(int x){
        return x2Id(x);
    }

    int operator[](int x){
        return id2X(x);
    }

    int size(){
        if(!initialized)init();
        return xs.size();
    }
}CC;

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
        while(k<=bit.size()){
            bit[k]=bit[k]+dx;
            k+=(k&(-k));
        }
    }

    ll sum(int k)const{
        ll s=0;
        while(k>0){
            s=s+bit[k];
            k-=(k&(-k));
        }
        return s;
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
    vector<int> a(n);
    vector<ll> ans;
    CC xs;
    xs.add(0);
    rep(i,n){
        scanf("%d",&a[i]);
        xs.add(a[i]);
    }
    BIT count(xs.size()),sum(xs.size());
    //printf("    ");rep(i,xs.size()-1)printf("%d ",xs[i+1]);puts("");
    rep(i,m){
        count.add(xs(a[i]),1);
        sum.add(xs(a[i]),a[i]);
    }
    auto search=[&](){
        int left=1,right=count.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(count.sum(mid)<k)
                left=mid+1;
            else
                right=mid;
        }
        return left;
    };
    for(;i<n;i++){
        //printf("cnt:");count.show();
        //printf("sum:");sum.show();
        j=search();
        //printf("j:%d\n",j);
        ans.push_back(sum.sum(j)-xs[j]*(count.sum(j)-k));
        count.add(xs(a[i-m]),-1);
        count.add(xs(a[i]),1);
        sum.add(xs(a[i-m]),-a[i-m]);
        sum.add(xs(a[i]),a[i]);
    }
    j=search();
    ans.push_back(sum.sum(j)-xs[j]*(count.sum(j)-k));
    rep(i,ans.size()-1)
        printf("%lld ",ans[i]);
    printf("%lld\n",ans[i]);
    return 0;
}