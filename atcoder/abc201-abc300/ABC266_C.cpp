/*アルゴリズムと工夫点(Convex Quadrilateral/CPU: 1 ms Memory: 3692 KB  Length: 908 B)
始点が共通の2ベクトルa,bについて，aを始点を中心とした回転によってbと向きを合わせることができる時，
・反時計回りに180度以下の回転で合わせられる:cross(a,b)>=0
・時計回りに180度以下の回転で合わせられる:cross(a,b)<0
が成立する．
これを利用すればよい．最悪計算量は O(1)で高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Point{
    int x,y;

    Point(int xx=0,int yy=0):x(xx),y(yy){}

    Point operator-(const Point& k)const{
        return Point(x-k.x,y-k.y);
    }

    bool operator<(const Point& k)const{
        return x==k.x?y<k.y:x<k.x;
    }
};

int cross(Point& a,Point& b){
    return a.x*b.y-a.y*b.x;
}

int main(){
    int i;
    const int N=4;
    vector<Point> ipt(N);
    Point a,b;
    rep(i,N)scanf("%d%d",&ipt[i].x,&ipt[i].y);
    rep(i,N){
        a=ipt[(i+1)%N]-ipt[i];
        b=ipt[(N+i-1)%N]-ipt[i];
        //printf("a(%d,%d) b(%d,%d) cross(a,b)=%d\n",a.x,a.y,b.x,b.y,cross(a,b));
        if(cross(a,b)<0){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}