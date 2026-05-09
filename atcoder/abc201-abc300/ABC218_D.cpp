/*アルゴリズムと工夫点(Rectangles/CPU: 9 ms Memory: 4296 KB  Length: 2130 B)
四角形は基本的に，対角線の2点が決まると，他の2点も決まることが多い．今回はx軸,y軸の2つと平行でなければならないから，一意に定まる．
平行の条件が無くても，「対角線の長さが等しく，互いに中点で交わる」という条件から絞り込むことが可能．
※2点の選び方に矛盾が無いか，調べること．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

typedef class CoordinateCompression{
    int MIN_X,MAX_X;
    bool initialized;
    vector<int> xs;
public:
    CoordinateCompression(int mmin=0,int mmax=(int)(1e9)+1):MIN_X(mmin),MAX_X(mmax),initialized(false){}
    
    void add(int x){
        if(MIN_X<=x-1&&x-1<=MAX_X)
            xs.push_back(x-1);
        if(MIN_X<=x&&x<=MAX_X)
            xs.push_back(x);
        if(MIN_X<=x+1&&x+1<=MAX_X)
            xs.push_back(x+1);
        initialized=false;
    }

    void init(){
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
        initialized=true;
    }

    int x2Id(int x){
        if(!initialized)init();
        int left=0,right=xs.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(xs[mid]<x)
                left=mid+1;
            else
                right=mid;
        }
        return left;
    }

    int id2X(int id){
        if(!initialized)init();
        return xs[id];
    }

    int operator()(int x){
        return x2Id(x);
    }

    int operator[](int x){
        return id2X(x);
    }

    int size(){
        return xs.size();
    }
}CC;

typedef pair<int,int> p;

int n;
vector<p> ipt;
CC xys;

int main(){
    int i,j,cnt=0,k;
    scanf("%d",&n);
    vector<p> ipt=vector<p>(n);
    rep(i,n){
        scanf("%d%d",&ipt[i].first,&ipt[i].second);
        xys.add(ipt[i].first);
        xys.add(ipt[i].second);
    }
    xys(ipt[i].first);
    vector<vector<bool> > f(xys.size(),vector<bool>(xys.size(),false));
    rep(i,n){
        ipt[i].first=xys(ipt[i].first);
        ipt[i].second=xys(ipt[i].second);
        f[ipt[i].first][ipt[i].second]=true;
    }
    rep(i,n)rep(j,i){
        if(ipt[j].first!=ipt[i].first&&ipt[j].second!=ipt[i].second){
            cnt+=(f[ipt[i].first][ipt[j].second]&&f[ipt[j].first][ipt[i].second]);
            //if(f[ipt[i].first][ipt[j].second]&&f[ipt[j].first][ipt[i].second]){vector<p> tmp;tmp.push_back(ipt[i]);tmp.push_back(tmp[j]);tmp.push_back(p(ipt[i].first,ipt[j].second));tmp.push_back(p(ipt[j].first,ipt[i].second));rep(k,4)printf("(%d,%d) ",xys[ipt[k].first],xys[ipt[k].second]);puts("");}
        }
    }
    printf("%d\n",cnt/2);
    return 0;
}