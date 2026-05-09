/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)
集合の同値判定->ハッシュ法を用いて高速化できる
登場する値それぞれに別の乱数を割り当て，ある集合Aのハッシュ値を集合に含まれる値のXORとする手法．
※既に登場した値は'0'にしておくなど対処する事．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<random>
#include<time.h>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
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
        if(!initiated)init();
        return xs.size();
    }
}CC;

int n,q;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n),b(n);
    CC xs;
    set<int> v;
    xs.add(0);
    rep(i,n){
        scanf("%d",&a[i]);
        if(v.find(a[i])!=v.end())a[i]=0;
        xs.add(a[i]);
        v.insert(a[i]);
    }
    v=set<int>();
    rep(i,n){
        scanf("%d",&b[i]);
        if(v.find(b[i])!=v.end())b[i]=0;
        xs.add(b[i]);
        v.insert(b[i]);
    }

    mt19937_64 mt_for_construct(time(NULL));
    vector<ull> x_to_hash(xs.size());
    rep(i,xs.size())x_to_hash[i]=mt_for_construct();
    vector<ull> sum_a(n+1,0),sum_b(n+1,0);
    x_to_hash[xs(0)]=0;
    rep(i,n){
        sum_a[i+1]=sum_a[i]^x_to_hash[xs(a[i])];
        sum_b[i+1]=sum_b[i]^x_to_hash[xs(b[i])];
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&i,&j);
        printf("%s\n",sum_a[i]==sum_b[j]?"Yes":"No");
    }
    return 0;
}