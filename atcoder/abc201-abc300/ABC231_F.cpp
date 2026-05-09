/*アルゴリズムと工夫点(Jealous Two/CPU: 112 ms Memory: 7192 KB  Length: 2559 B)
座標圧縮+平面走査+BIT で解ける．
(Ai,Bi)が全く同じ点に対する処理に気を付けること．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct CordinatedCompression{
    bool initiated;
    vector<int> xs;

    CordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }

    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }

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

    int size(){
        return xs.size();
    }
}CC;

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
        rep(i,bit.size()-2)
            printf("%lld ",sum(i+1)-sum(i));
        printf("%lld\n",sum(i+1)-sum(i));
    }
}BIT;

typedef pair<int,int> p;

int n;

int main(){
    int i,j,k;
    ll sum=0;
    scanf("%d",&n);
    vector<p> ipt(n);
    CC xs;
    xs.add(0);
    rep(i,n){
        scanf("%d",&ipt[i].first);
    }
    rep(i,n){
        scanf("%d",&ipt[i].second);
        ipt[i].second++;
        xs.add(ipt[i].second);
    }
    auto greater_=[](p a,p b)->bool{
        return a.first<b.first||(a.first==b.first&&a.second>b.second);
    };
    sort(ipt.begin(),ipt.end(),greater_);
    rep(i,n)ipt[i].second=xs(ipt[i].second);
    BIT tree(xs.size());
    k=1;
    rep(i,n){
        if(i>0&&ipt[i-1]==ipt[i]){
            k++;
            sum+=j;
        }else{
            sum+=(ll)k*(k-1);
            k=1;
            j=tree.sum(xs.size())-tree.sum(ipt[i].second-1);
            sum+=j;
        }
        tree.add(ipt[i].second,1);
    }
    sum+=(ll)k*(k-1);
    printf("%lld\n",sum+n);
    return 0;
}