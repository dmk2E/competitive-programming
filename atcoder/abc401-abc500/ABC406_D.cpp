/*アルゴリズムと工夫点(Garbage Removal/CPU: 411 ms Memory: 43908 KB  Length: 2322 B)
座圧+(setの高速要素挿入&削除)を利用して解く．
つまり，入力されたx座標毎，y座標毎にsetを持って管理して解けばよい．
最悪計算量は O(N*log2(N))<10^7 となり十分高速．
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

typedef class CordinatedCompression{
    bool initiated;
    vector<int> xs;
public:
    CordinatedCompression(){
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

int h,w,n,q;

int main(){
    int i,j;
    scanf("%d%d%d",&h,&w,&n);
    vector<int> x(n),y(n);
    CC xs,ys;
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
        xs.add(x[i]);
        ys.add(y[i]);
    }
    vector<set<int> > x_to_g(xs.size()),y_to_g(ys.size());
    rep(i,n){
        x_to_g[xs(x[i])].insert(ys(y[i]));
        y_to_g[ys(y[i])].insert(xs(x[i]));
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d",&i);
            int x=xs(i);
            if(i!=xs[x])puts("0");
            else{
                printf("%ld\n",x_to_g[x].size());
                for(int y:x_to_g[x]){
                    y_to_g[y].erase(x);
                }
                if(x_to_g[x].size()>0)x_to_g[x].clear();
            }
        }else{
            scanf("%d",&i);
            int y=ys(i);
            if(i!=ys[y])puts("0");
            else{
                printf("%ld\n",y_to_g[y].size());
                for(int x:y_to_g[y]){
                    x_to_g[x].erase(y);
                }
                if(y_to_g[y].size()>0)y_to_g[y].clear();
            }
        }
    }
    return 0;
}