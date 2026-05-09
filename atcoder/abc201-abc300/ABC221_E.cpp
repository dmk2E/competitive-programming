/*アルゴリズムと工夫点(LEQ/CPU: 318 ms Memory: 15328 KB  Length: 2800 B)
両端の値がal,ar(aにおいて前からi番目の要素aiとする)であり，al<=arならば条件を満たす部分列の数は2^(r-l-1)=2^(r-1)*(1/2)^(l)個となる．
arを固定すると，条件を満たすalさえ分かればよく，つまり条件を満たす(1/2)^(l)の総和が分かればよい．
従って，座標圧縮+平面走査+BITで解く．
最悪計算量はO(N*(log2(N)+log2(MOD)))<10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

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
    int MOD=998244353;
    vector<ll> bit;
public:
    BinaryIndexedTree(int n=0){
        bit=vector<ll>(n,0);
    }

    void init(int n){
        bit=vector<ll>(n,0);
    }

    void add(int k,long long dx){
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

    int size(){
        return (int)bit.size();
    }

    void show(){
        int i;
        rep(i,bit.size()-1)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

const int MOD=998244353;

int power(int x,int a){
    if(a==0)return 1;
    ll res=power((int)(((ll)x*x)%MOD),a/2);
    if(a%2==1)
        res*=x;
    return res%MOD;
}

int n;
vector<int> a;

int main(){
    int i,j;
    ll ans=0;
    CC xs;
    scanf("%d",&n);
    a=vector<int>(n);
    xs.add(0);
    rep(i,n){
        scanf("%d",&a[i]);
        xs.add(a[i]);
    }
    BIT bit(xs.size());
    rep(i,n){
        if(i>0)
            ans=(ans+((ll)power(2,i-1)*bit.sum(xs(a[i])))%MOD)%MOD;
        bit.add(xs(a[i]),power(power(2,i),MOD-2));
        //printf("id:%d\n",xs(a[i]));
    }
    printf("%lld\n",ans);
    return 0;
}