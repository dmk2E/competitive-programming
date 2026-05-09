/*アルゴリズムと工夫点(Wrapping Chocolate/CPU: 324 ms Memory: 40712 KB  Length: 2133 B)
平面走査をする．縦の長さをx軸，横の長さをy軸とし，x軸を時系列に見ていき，y軸に関してはmultisetで管理する．
まず，チョコレートが存在する場合そのy座標をmultisetに入れる．箱が存在する場合，その箱のy座標以下で最大のy座標を持つチョコレートを入れるようにする．
座標が大きいので座標圧縮をすること．最悪計算量は，O((N+M)*log2(N+M))<10^7 となり十分高速．
※同じx座標では，チョコレートを先にmultisetに入れてから，箱の操作をすればよい．
※初見で解けた!嬉しい!
*/
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
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
        return xs.size();
    }
}CC;

typedef pair<int,bool> P;//(値，箱か否か)

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<int> a(n),b(n),c(m),d(m);
    CC xs,ys;
    ys.add(-1);
    rep(i,n){
        scanf("%d",&a[i]);
        xs.add(a[i]);
    }
    rep(i,n){
        scanf("%d",&b[i]);
        ys.add(b[i]);
    }
    rep(i,m){
        scanf("%d",&c[i]);
        xs.add(c[i]);
    }
    rep(i,m){
        scanf("%d",&d[i]);
        ys.add(d[i]);
    }
    vector<vector<P> > event(xs.size());
    rep(i,n)event[xs(a[i])].push_back(P(ys(b[i]),false));
    rep(i,m)event[xs(c[i])].push_back(P(ys(d[i]),true));
    multiset<int> tree;
    multiset<int>::iterator it;
    rep(i,event.size()){
        // printf("x:%d\n",i);printf("chocorate:%d\n",(int)tree.size());
        rep(j,event[i].size()){
            if(event[i][j].second){
                it=tree.upper_bound(event[i][j].first);
                if(it!=tree.begin()){
                    it--;
                    tree.erase(it);
                }
            }else tree.insert(event[i][j].first);
        }
        // printf("chocorate:%d\n",(int)tree.size());
    }
    printf("%s\n",tree.size()==0?"Yes":"No");
    return 0;
}