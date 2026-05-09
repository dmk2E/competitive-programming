/*アルゴリズムと工夫点(K-colinear Line/CPU: 40 ms Memory: 7256 KB  Length: 1557 B)

*/
#include<iostream>
#include<vector>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class fraction{ 
    ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}

public:
    ll top,btm;
    fraction(ll ttop=0,ll bbtm=1):top(ttop),btm(bbtm){
        if(btm==0){top=1;return ;}
        if(btm<0)btm=-btm,top=-top;
        ll g=gcd(abs(top),abs(btm));
        top/=g;btm/=g;
    }

    bool operator<(const fraction& k)const{
        return top*k.btm<k.top*btm;
    }

    bool operator==(const fraction& k)const{
        return top==k.top&&btm==k.btm;
    }
}Frac;

struct Line{
    Frac f,y;

    Line(Frac ff,int xx=0,int yy=0):f(ff){
        y=Frac(f.top*xx+f.btm*yy,f.btm);
    }

    bool operator<(const Line& k)const{
        return f==k.f?y<k.y:f<k.f;
    }
};

int n,k;

int main(){
    int i,j,ii,cnt;
    scanf("%d%d",&n,&k);
    if(k==1){
        puts("Infinity");
        return 0;
    }
    vector<int> x(n),y(n);
    set<Line> ls;
    set<int> ys,xs;
    rep(i,n)scanf("%d%d",&x[i],&y[i]);
    rep(i,n)rep(j,i){
        cnt=0;
        rep(ii,n)cnt+=(((ll)y[ii]-y[i])*(x[j]-x[i])==((ll)y[j]-y[i])*(x[ii]-x[i]));
        if(cnt>=k){
            if(x[j]-x[i]==0)xs.insert(x[i]);
            else if(y[j]-y[i]==0)ys.insert(y[i]);
            else ls.insert(Line(Frac(y[j]-y[i],x[j]-x[i]),-x[i],y[i]));
        }
    }
    printf("%ld\n",ls.size()+ys.size()+xs.size());
    return 0;
}