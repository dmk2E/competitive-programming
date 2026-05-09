/*アルゴリズムと工夫点(InterSections/CPU: 769 ms Memory: 76248 KB  Length: 4885 B)
2つのパラメータを扱うデータにおいて，大小関係を考える場合，その二つのパラメータを軸とする平面で考えてみる．今回は，解を点(l,r)とするときの平面とする．
※平面走査を行うとき，時系列として扱うパラメータxの値それぞれでeventを管理すればよい．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX (int)(1e9)
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

const int NIL=-1;

typedef struct data{
    int x,delay,y;

    data(int xx=NIL,int ddelay=0,int yy=0):x(xx),delay(ddelay),y(yy){}
}Data;

typedef class SegTree{
    int n,nn;
    vector<Data> tree;
public:
    SegTree(int nnn=0){
        nn=nnn;
        n=1;
        while(n<nn)n*=2;
        tree=vector<Data>(2*n-1);
    }

    void eval(int k,int l,int r){
        if(tree[k].delay!=0){
            tree[k].x+=tree[k].delay;
            if(r-l>1){
                tree[2*k+1].delay+=tree[k].delay;
                tree[2*k+2].delay+=tree[k].delay;
            }
            tree[k].delay=0;
        }
    }

    Data mmax(Data& now,Data left,Data right){
        if(left.x==right.x){
            now.x=left.x;
            now.y=left.y<right.y?left.y:right.y;
        }else if(left.x>right.x){
            now.x=left.x;
            now.y=left.y;
        }else{
            now.x=right.x;
            now.y=right.y;
        }
        return Data(now.x,0,now.y);
    }

    void update(int k,int a){
        k+=n-1;
        tree[k].x=a;
        tree[k].y=k-n+1;
        while(k>0){
            k=(k-1)/2;
            mmax(tree[k],tree[2*k+1],tree[2*k+2]);
        }
    }

    void mapping(int a,int b,int k,int l,int r,int dx){
        if(r==-1)r=n;
        eval(k,l,r);
        if(b<=l||r<=a)return ;
        if(a<=l&&r<=b){
            tree[k].delay+=dx;
            eval(k,l,r);
            return ;
        }
        mapping(a,b,2*k+1,l,(l+r)/2,dx);mapping(a,b,2*k+2,(l+r)/2,r,dx);
        mmax(tree[k],tree[2*k+1],tree[2*k+2]);
    }

    Data query(int a,int b,int k,int l,int r){
        if(r==-1)r=n;
        if(b<=l||r<=a)return Data(NIL);
        eval(k,l,r);
        if(a<=l&&r<=b)return tree[k];
        Data tmp;
        return mmax(tmp,query(a,b,2*k+1,l,(l+r)/2),query(a,b,2*k+2,(l+r)/2,r));
    }

    void show(){int i;rep(i,nn-1)printf("%d ",tree[i+n-1].x);printf("%d\n",tree[i+n-1].x);}
}SegT;

typedef struct rects{
    int lx,rx,ly,ry;

    rects(int llx=0,int rrx=0,int lly=0,int rry=0):lx(llx),rx(rrx),ly(lly),ry(rry){}
}Rects;

typedef struct event{
    int x,y,d;

    event(int xx=NIL,int yy=0,int dd=0):x(xx),y(yy),d(dd){};
}Event;

int n;

int main(){
    int i,j,aX=0,aY=1,mmax=0;
    Data now;
    scanf("%d",&n);
    vector<Rects> rects;
    while(n--){
        scanf("%d%d",&i,&j);
        rects.push_back(Rects(0,i,i+1,j));
        rects.push_back(Rects(i+1,j,j+1,MAX+1));
    }
    CC xs(0,MAX+3),ys(0,MAX+3);
    for(auto x:rects){
        xs.add(x.lx);xs.add(x.rx);
        ys.add(x.ly);ys.add(x.ry);
    }
    vector<vector<Event> > events(xs.size());
    for(auto&& now:rects){
        now.lx=xs(now.lx);now.rx=xs(now.rx);
        now.ly=ys(now.ly);now.ry=ys(now.ry);
        events[now.lx].push_back(Event(now.ly,now.ry,1));
        events[now.rx].push_back(Event(now.ly,now.ry,-1));
    }
    SegT tree(ys.size());
    rep(i,ys.size())
        tree.update(i,0);
    rep(i,xs.size()){
        for(Event tmp:events[i]){
            //printf("event:%d %d %d\n",tmp.x,tmp.y,tmp.d);
            tree.mapping(tmp.x,tmp.y,0,0,NIL,tmp.d);
        }
        now=tree.query(0,ys.size(),0,0,NIL);
        //printf("now:%d %d\n",now.x,now.y);
        //tree.show();
        if(xs.id2X(i)<ys.id2X(now.y)&&now.x>mmax){
            mmax=now.x;
            aX=xs[i];
            aY=ys[now.y];
        }
    }
    printf("%d %d\n",aX,aY);
    return 0;
}