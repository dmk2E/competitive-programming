/*アルゴリズムと工夫点(Diagonal Separation/CPU: 60 ms Memory: 5692 KB  Length: 873 B)
あるマス(x,y)が黒である時，(x,1),(x,2),...,(x,y-1)と(1,y),(2,y),...,(x-1,y)も黒である必要がある．
そのため，条件を満たすには，矩形[1,x][1,y]の範囲全てが黒である必要がある．
したがって，N個の点を辞書順に見ていくことで，その条件を満たせるか逐次判定すればよい．
この時，それまで巡回した白マスのy座標の最小値を保持して置くだけでよい．
最悪計算量は O(M*log2(M))
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Point{
    int x,y;
    bool c;

    Point(int xx=0,int yy=0,bool c=false):x(xx),y(yy){}

    bool operator<(const Point& k)const{
        return x==k.x?(y==k.y?c:y<k.y):x<k.x;
    }
};

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<Point> ipt(m);
    rep(i,m){
        scanf("%d%d",&ipt[i].x,&ipt[i].y);
        getchar();
        ipt[i].c=(getchar()=='B');
    }
    sort(ipt.begin(),ipt.end());
    j=n+1;
    rep(i,m){
        if(ipt[i].c){
            if(j<=ipt[i].y){
                puts("No");
                return 0;
            }
        }else
            j=min(j,ipt[i].y);
    }
    puts("Yes");
    return 0;
}