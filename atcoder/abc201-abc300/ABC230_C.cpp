/*アルゴリズムと工夫点(X drawing/CPU: 270 ms Memory: 12752 KB  Length: 1436 B)
各操作それぞれで描画する直線の，指定された範囲中の始点を求めてから1つずつ描画する．
※考えずらい問題は，場合分けして簡単な問題に分割する．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct point{
    ll y,x;

    point(ll yy=0,ll xx=0):y(yy),x(xx){}
}Point;

ll n,a,b,p,q,r,s;

int main(){
    int i,j;
    Point s1,t1,s2,t2;
    scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&a,&b,&p,&q,&r,&s);
    vector<string> ans(q-p+1,string(s-r+1,'.'));
    s1=Point(a+max(1-a,1-b),b+max(1-a,1-b));t1=Point(a+min(n-a,n-b),b+min(n-a,n-b));
    s2=Point(a+max(1-a,b-n),b-max(1-a,b-n));t2=Point(a+min(n-a,b-1),b-min(n-a,b-1));
    auto adjust=[&](Point& k)->void{
        if(k.y<p)k=Point(p,b+p-a);
            if(p<=k.y&&k.y<=q&&r<=k.x&&k.x<=s)return ;
        if(k.x<r)k=Point(a+r-b,r);
            if(p<=k.y&&k.y<=q&&r<=k.x&&k.x<=s)return ;
    };
    auto aadjust=[&](Point& k)->void{
        if(k.y<p)k=Point(p,b-p+a);
            if(p<=k.y&&k.y<=q&&r<=k.x&&k.x<=s)return ;
        if(k.x>s)k=Point(a+b-s,s);
            if(p<=k.y&&k.y<=q&&r<=k.x&&k.x<=s)return ;
    };
    adjust(s1);
    aadjust(s2);
    while(p<=s1.y&&s1.y<=q&&r<=s1.x&&s1.x<=s&&s1.y<=t1.y&&s1.x<=t1.x){
        ans[s1.y-p][s1.x-r]='#';
        s1.y++;s1.x++;
    }
    while(p<=s2.y&&s2.y<=q&&r<=s2.x&&s2.x<=s&&s2.y<=t2.y&&s2.x>=t2.x){
        ans[s2.y-p][s2.x-r]='#';
        s2.y++;s2.x--;
    }
    rep(i,ans.size())cout<<ans[i]<<endl;
    return 0;
}