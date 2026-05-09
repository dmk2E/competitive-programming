/*アルゴリズムと工夫点(Compression/CPU: 27 ms Memory: 4216 KB  Length: 1133 B)
座標圧縮するだけ．
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

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n);
    CC xs;
    rep(i,n){
        scanf("%d",&a[i]);
        xs.add(a[i]);
    }
    rep(i,n)a[i]=xs(a[i])+1;
    rep(i,n-1)printf("%d ",a[i]);printf("%d\n",a[i]);
    return 0;
}