/*アルゴリズムと工夫点(フ/CPU: 390 ms Memory: 38308 KB  Length: 1316 B)
フの角度を1次元に落とし，区間が被らないような最大の区間数を求める「区間スケジューリング」で解ける．
※「区間スケジューリング」:<i>右端で昇順にソート <ii>その時に，「今まで選択した区間の最大の右端の値maxR」以上の左端を持つ区間[l,r]を選び，maxR=rとする の貪欲法
※ある点xより大きい時
*/
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class fraction{ 
    ll top,btm;

    ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}

public:
    fraction(ll ttop=0,ll bbtm=1):top(ttop),btm(bbtm){
        if(btm==0){top=1;return ;}
        if(btm<0){
            btm=-btm;
            top=-top;
        }
        ll g=gcd(top,btm);
        top/=g;btm/=g;
    }

    bool operator<(const fraction& k)const{
        return top*k.btm<k.top*btm;
    }

    bool operator==(const fraction& k)const{
        return top==k.top&&btm==k.btm;
    }
}Frac;

typedef pair<int,int> p;

int n;

int main(){
    int i;
    scanf("%d",&n);
    vector<int> x(n),y(n);
    rep(i,n)scanf("%d%d",&x[i],&y[i]);
    vector<Frac> lf(n),rf(n);
    rep(i,n)lf[i]=Frac(x[i]-1,y[i]);
    rep(i,n)rf[i]=Frac(x[i],y[i]-1);
    map<Frac,int> fs;
    rep(i,n)fs[lf[i]]=fs[rf[i]]=0;
    i=0;
    for(auto&& p :fs)p.second=i++;
    vector<p> d;
    rep(i,n)d.push_back(p(fs[rf[i]],fs[lf[i]]));
    sort(d.begin(),d.end());
    int maxX=-1,ans=0;
    for(auto [r,l]:d){
        if(l>=maxX)maxX=r,ans++;
    }
    printf("%d\n",ans);
    return 0;
}