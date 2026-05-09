/*アルゴリズムと工夫点(Trapezium/CPU: 663 ms Memory: 81608 KB  Length: 2806 B)
数え上げで解く．
どの3点も同一直線上にないため，単純に線分を列挙し，傾きが同じもので分類し，その個数から解を数え上げる．
この時，平行四辺形の数の分は重複してしまうため，取り除く．
平行四辺形の辺については，(傾き，長さ)の組で管理する．
最悪計算量は，O(N^(2)*log2(N^(2))+N^(2)*log2(max(Xi,Yi)))<10^8 となり，間に合う．
※ mapを使うとTLEしてしまうため，「可変長配列+ソート+線形探索」で数え上げることで高速化している．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class Fraction{
public:
    ll top,btm;

private:
    /// @brief ユークリッドの互除法で最大公約数を求める
    /// @param a 1つ目の整数
    /// @param b 2つ目の整数
    /// @return 2つの整数a,bの最大公約数
    ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}

public:
    /// @brief 分数クラス
    /// @param ttop 分子
    /// @param bbtm 分母
    Fraction(ll ttop=0,ll bbtm=1):top(ttop),btm(bbtm){
        if(btm==0){top=1;return ;}
        if(btm<0)btm=-btm,top=-top;
        ll g=gcd(abs(top),btm);
        if(g!=0)top/=g;btm/=g;
    }

    Fraction operator+(const Fraction& k)const{
        return Fraction(top*k.btm+btm*k.top,btm*k.btm);
    }

    Fraction operator-(const Fraction& k)const{
        return Fraction(top*k.btm-btm*k.top,btm*k.btm);
    }

    Fraction operator*(const ll& k)const{
        return Fraction(top*k,btm);
    }

    Fraction operator*(const Fraction& k)const{
        return Fraction(top*k.top,btm*k.btm);
    }

    Fraction operator/(const Fraction& k)const{
        return Fraction(top*k.btm,btm*k.top);
    }

    bool operator<(const Fraction& k)const{
        return top*k.btm<k.top*btm;
    }

    bool operator==(const Fraction& k)const{
        return top==k.top&&btm==k.btm;
    }

    bool operator!=(const Fraction& k)const{
        return !((*this)==k);
    }

    /// @brief 分数表示
    void show(){
        printf("%lld / %lld\n",top,btm);
    }
}Frac;

struct Point{
    ll y,x;

    Point(ll y=0,ll x=0):y(y),x(x){}

    Point operator-(const Point& k)const{
        return Point(y-k.y,x-k.x);
    }

    ll norm(){
        return y*y+x*x;
    }
};

typedef pair<Fraction,ll> P;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<Point> p(n);
    rep(i,n)scanf("%lld%lld",&p[i].x,&p[i].y);
    vector<Fraction> seg1;
    vector<P> seg2;
    rep(i,n)rep(j,i){
        Point a=p[i],b=p[j];
        seg1.push_back(Fraction(b.y-a.y,b.x-a.x));
        seg2.push_back(P(Fraction(b.y-a.y,b.x-a.x),(b-a).norm()));
    }
    sort(seg1.begin(),seg1.end());
    sort(seg2.begin(),seg2.end());
    ll ans=0,tmp=0;
    i=0;
    while(i<seg1.size()){
        ll cnt=0;
        Fraction f=seg1[i];
        while(i<seg1.size()&&f==seg1[i])cnt++,i++;
        ans+=cnt*(cnt-1)/2;
    }
    i=0;
    while(i<seg2.size()){
        ll cnt=0;
        P f=seg2[i];
        while(i<seg1.size()&&f==seg2[i])cnt++,i++;
        tmp+=cnt*(cnt-1)/2;
    }
    printf("%lld\n",ans-tmp/2);
    return 0;
}