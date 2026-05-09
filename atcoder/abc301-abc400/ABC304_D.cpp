/*アルゴリズムと工夫点(A Piece of Cake/CPU: 222 ms Memory: 30692 KB  Length: 2368 B)
イチゴの座標を順に巡回して数え上げる．
ケーキのピースの情報は，そのピース領域 (y∈[b_{i},b_{i+1}], x∈[a_{i},a_{i+1}])の時，(Y,X)=(b_{i}, a_{i})という形で保持する．
y座標の昇順，x座標の昇順に巡回し，ピース毎のイチゴの数を数え上げる．
あるイチゴが存在するピース情報は，Yについては尺取り法の要領で，順に加算していくだけでよいが，Xについては二分探索を用いて高速化する．
情報として保持するピースの数はNを超えないため，最悪計算量は，O(A+B+N*(log2(N)+log2(A)))<10^8 となり間に合う．
※実装では分かりやすさのために座圧しているが，実際はそのまま座標をソートして保持するだけでよい．
*/
#include<iostream>
#include<vector>
#include<map>
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

struct Point{
    int y,x;

    Point(int yy=0,int xx=0):y(yy),x(xx){}

    bool operator<(const Point& k)const{
        return y==k.y?x<k.x:y<k.y;
    }
};

int w,h,n,a,b;

int main(){
    int i,j;
    scanf("%d%d%d",&w,&h,&n);
    vector<Point> ipt(n);
    map<Point,int> piece_to_cnt;
    CC ys;
    rep(i,n){
        scanf("%d%d",&ipt[i].x,&ipt[i].y);
        ys.add(ipt[i].y);
    }
    vector<vector<int> > ps(ys.size());
    rep(i,n)ps[ys(ipt[i].y)].push_back(ipt[i].x);
    scanf("%d",&a);
    vector<int> line_x(a+2);
    line_x[0]=0;rep(i,a)scanf("%d",&line_x[i+1]);line_x[i+1]=w;
    scanf("%d",&b);
    vector<int> line_y(b+2);
    line_y[0]=0;rep(i,b)scanf("%d",&line_y[i+1]);line_y[i+1]=h;
    int now_y=0;
    rep(i,ys.size()){
        while(line_y[now_y]>=ys[i]||ys[i]>=line_y[now_y+1])now_y++;
        for(int x:ps[i]){
            int now_x=lower_bound(line_x.begin(),line_x.end(),x)-line_x.begin()-1;
            piece_to_cnt[Point(now_y,now_x)]++;
        }
    }
    i=n+1;
    j=-1;
    for(auto& d:piece_to_cnt){
        i=min(i,d.second);
        j=max(j,d.second);
    }
    if(piece_to_cnt.size()<((ll)a+1)*(b+1))i=0;
    printf("%d %d\n",i,j);
    return 0;
}