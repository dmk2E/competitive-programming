/*アルゴリズムと工夫点(Laser Marking/CPU: 3 ms Memory: 3900 KB  Length: 2096 B)
どの線分から巡回するか，順列を全て試し，描画順序を固定する．
そのうえで，「線分の端点の内どちらから描画するか」をビット全探索する．
最悪計算量はO(2^(N)*N!)<10^5 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct point{
    int y,x;

    point(int xx=0,int yy=0):x(xx),y(yy){}

    point operator-(point k)const{
        return point(x-k.x,y-k.y);
    }

    int norm(){
        return y*y+x*x;
    }

    double dis(){
        return sqrt(norm());
    }
}Point;

typedef pair<Point,Point> p;

int n,s,t;

int main(){
    int i,j;
    double mmin=(1e18),tmp;
    Point now;
    scanf("%d%d%d",&n,&s,&t);
    vector<p> ipt(n);
    rep(i,n){
        scanf("%d%d%d%d",&ipt[i].first.x,&ipt[i].first.y,&ipt[i].second.x,&ipt[i].second.y);
    }
    string per;
    rep(i,n)per+=(char)(i+(int)'0');
    auto cal=[&](Point& now,int nxt,int state)->double{
        double sum=0,tmp1,tmp2;
        point vec1=ipt[nxt].first-now,vec2=ipt[nxt].second-now;
        if(state&(1<<nxt)){
            //if(per=="102"&&state==6)printf("(%d,%d)->(%d,%d)\n",now.x,now.y,ipt[nxt].first.x,ipt[nxt].first.y);
            tmp1=((double)vec1.dis()/s);
            tmp2=(ipt[nxt].second-ipt[nxt].first).dis()/t;
            sum+=((double)vec1.dis()/s)+(ipt[nxt].second-ipt[nxt].first).dis()/t;
            now=ipt[nxt].second;
        }else{
            //if(per=="102"&&state==6)printf("(%d,%d)->(%d,%d)\n",now.x,now.y,ipt[nxt].second.x,ipt[nxt].second.y);
            tmp1=((double)vec1.dis()/s);
            tmp2=(ipt[nxt].second-ipt[nxt].first).dis()/t;
            sum+=((double)vec2.dis()/s)+(ipt[nxt].second-ipt[nxt].first).dis()/t;
            now=ipt[nxt].first;
        }
        //if(per=="102"&&state==6)printf("tmp1:%.8f tmp2:%.8f sum:%.8f\n",tmp1,tmp2,sum);
        return sum;
    };
    do{
        rep(i,1<<n){
            tmp=0;
            now=Point(0,0);
            rep(j,n)tmp+=cal(now,per[j]-'0',i);
            if(tmp<mmin)mmin=tmp;
        }
    }while(next_permutation(per.begin(),per.end()));
    printf("%.8f\n",mmin);
    return 0;
}