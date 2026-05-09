/*アルゴリズムと工夫点(RLE Moving/CPU: 26 ms Memory: 4924 KB  Length: 2893 B)
シミュレーションで解く．
愚直なシミュレーションはできないので，高橋君と青木君それぞれが方向転換するタイミングで区間を区切り，その区間で何回同じマスに存在したかを数え上げる．
同じマスにいた数の数え上げは，場合分けの数が多いため，一次方程式を解くことで行う．
最悪計算量は，O(M+L) < 10^6 となり十分高速．
※ 場合分けの数を減らすため，一次方程式を用いた実装に持ち込むことは覚えておく．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int id,dist;

    Data(int id=0,int dist=0):id(id),dist(dist){}
};

struct Point{
    ll r,c;

    Point(ll r=0,ll c=0):r(r),c(c){}

    Point operator+(const Point& k)const{
        return Point(r+k.r,c+k.c);
    }

    Point operator-(const Point& k)const{
        return Point(r-k.r,c-k.c);
    }

    Point operator*(const int& k)const{
        return Point(r*k,c*k);
    }

    bool operator==(const Point& k)const{
        return r==k.r && c==k.c;
    }

    ll dist(){
        return abs(r)+abs(c);
    }
};

ll n;
int m,l;
const ll INF=(1e18),NIL=-1;

/// @brief 方向を対応するidに変換
/// @param c "URDL"のいずれか
/// @return 方向を示すid
int dir2Id(char c){
    int id=3;
    switch(c){
        case 'U':
            id=0;
            break;
        case 'R':
            id=1;
            break;
        case 'D':
            id=2;
            break;
        default:
            break;
    }
    return id;
}

/// @brief 一次方程式a*x + b = c*x + d を解く
/// @param a 係数
/// @param b y切片
/// @param c 係数
/// @param d y切片
/// @return 一次方程式の解
ll calcEqu(ll a,ll b,ll c,ll d){
    if(a==c)return (b==d) ? INF : NIL;
    if(b==d)return NIL;
    a-=c;d-=b;
    if(a<0)a=-a,d=-d;
    if(a%d!=0)return NIL;
    return a/d;
}

/// @brief 同じマスにいた回数を数え上げる
/// @param t 高橋君の現在の座標
/// @param dt 高橋君の移動量
/// @param a 青木君の現在の座標
/// @param da 青木君の移動量
/// @param dist 進む時間
/// @return 同じマスにいた回数
ll calc(const Point& t,const Point& dt,const Point& a,const Point& da,ll dist){
    ll solve_r = calcEqu(t.r,dt.r,a.r,da.r);
    ll solve_c = calcEqu(t.c,dt.c,a.c,da.c);
    if(solve_r == INF)swap(solve_r,solve_c);
    if(solve_r == INF)return dist;
    if(solve_c == INF && 0 < solve_r && solve_r <= dist)return 1;
    if(solve_r == solve_c && 0 < solve_r && solve_r <= dist)return 1;
    return 0;
}

int main(){
    int i,j;
    const int dy[]={-1,0,1,0},MAX_D=4;
    const int dx[]={0,1,0,-1};
    Point t,a;
    scanf("%lld%lld%lld%lld",&t.r,&t.c,&a.r,&a.c);
    scanf("%lld%d%d",&n,&m,&l);
    vector<Data> taka(m),aoki(l);
    rep(i,m){
        getchar();
        taka[i].id=dir2Id(getchar());
        scanf("%d",&taka[i].dist);
    }
    rep(i,l){
        getchar();
        aoki[i].id=dir2Id(getchar());
        scanf("%d",&aoki[i].dist);
    }
    int now_t=0,now_a=0;
    ll now=0,ans=0;
    while(now<n){
        int dist=min(taka[now_t].dist,aoki[now_a].dist);
        Point nxt_t=t+Point(dy[taka[now_t].id],dx[taka[now_t].id])*dist;
        Point nxt_a=a+Point(dy[aoki[now_a].id],dx[aoki[now_a].id])*dist;
        ans+=calc(
            t,
            Point(dy[taka[now_t].id],dx[taka[now_t].id]),
            a,
            Point(dy[aoki[now_a].id],dx[aoki[now_a].id]),
            dist
        );
        // 後処理
        now+=dist;
        swap(t,nxt_t);swap(a,nxt_a);
        taka[now_t].dist-=dist;aoki[now_a].dist-=dist;
        if(taka[now_t].dist==0)now_t++;
        if(aoki[now_a].dist==0)now_a++;
    }
    printf("%lld\n",ans);
    return 0;
}