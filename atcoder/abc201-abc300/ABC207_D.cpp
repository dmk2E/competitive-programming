/*アルゴリズムと工夫点(Congruence Points/CPU: 2 ms Memory: 3880 KB  Length: 1680 B)
1点に1点が対応するように固定する場合だと,平行移動量しか確定できない.そこで,A0,A1の2点を別の2点と対応づけるように固定する.この全探索はO(N^2)で済む.
どれか1点がどれか1点と一致しているかの判定->ソートしたうえで,全ての要素が一致するか判定すれば楽.
*/
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define EPS (1e-10)
using namespace std;

typedef struct point{
    int y,x;

    point(int yy=0,int xx=0):y(yy),x(xx){}

    double norm(){
        return y*y+x*x;
    }

    bool operator==(const point& k)const{
        return y==k.y&&x==k.x;
    }

    bool operator<(const point& k)const{
        return x==k.x?y<k.y:x<k.x;
    }

    point operator-(const point& k)const{
        return point(y-k.y,x-k.x);
    }

    point operator*(const point& k)const{
        return point(x*k.y+y*k.x,x*k.x-y*k.y);
    }
}Point;

typedef Point Vector;

int n;

vector<Point> create(vector<Point>& x,Vector l,Vector r){
    int i;
    vector<Point> u(n);
    rep(i,n)u[i]=x[i]-l;   //原点に移動
    rep(i,n)u[i]=u[i]*r;   //必要な分だけ回転
    sort(u.begin(),u.end());
    return u;
}

int main(){
    int i,j;
    scanf("%d",&n);
    vector<Point> s(n),t(n),ss,tt;
    Point a;
    rep(i,n)
        scanf("%d%d",&s[i].x,&s[i].y);
    rep(i,n)
        scanf("%d%d",&t[i].x,&t[i].y);
    if(n==1)
        puts("Yes");
    else{
        a=s[1]-s[0];
        rep(i,n){
            rep(j,n){
                if(i==j)
                    continue;
                if(a.norm()!=(t[j]-t[i]).norm())
                    continue;
                ss=create(s,s[0],t[j]-t[i]);
                tt=create(t,t[i],s[1]-s[0]);
                if(ss==tt){
                    puts("Yes");
                    return 0;
                }
            }
        }
        puts("No");
    }
    return 0;
}