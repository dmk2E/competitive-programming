/*アルゴリズムと工夫点(Cutting Woods/CPU: 227 ms Memory: 23664 KB  Length: 3394 B)
クエリ2を答えるには，指定された切れ目xiとした時の，([xi,l+1)における既に切られたxjの最小値)-([0,xi)における既に切られたxjの最大値)となる．
従って，区間[l,r)において，既に切られたxの最小値minXと最大値maxXを保持させるセグメント木を構築して考える．ここで要素xが(minX=MAX_L+2,maxX=-1)の時，まだ切られてないことを表し，初期値とする．
ただし，座標が非常に大きいため，座標圧縮を行う．
そうすると，各クエリに対する処理がO(log2(Q))で行える．
従って，最悪計算量はO(Q*log2(Q))<10^7 となり，高速．
※初見4完できた!
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_L (int)(1e9)
#define NIL -1
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

typedef struct data{
    int minX,maxX;

    data(int mminX=MAX_L+2,int mmax=-1):minX(mminX),maxX(mmax){}
}Data;

typedef class SegmentTree{
    int n,nn;
    vector<Data> tree;
public:
    SegmentTree(int nnn){
        nn=nnn;
        n=1;
        while(n<nn)n*=2;
        tree=vector<Data>(2*n-1);
    }

    void update(int k,int a){
        k+=n-1;
        tree[k].minX=tree[k].maxX=k-n+1;
        while(k>0){
            k=(k-1)/2;
            tree[k].minX=min(tree[2*k+1].minX,tree[2*k+2].minX);
            tree[k].maxX=max(tree[2*k+1].maxX,tree[2*k+2].maxX);
        }
    }

    Data query(int a,int b,int k,int l,int r){
        if(r<0)r=n;
        if(r<=a||b<=l)return Data();
        else if(a<=l&&r<=b)return tree[k];
        Data left=query(a,b,2*k+1,l,(l+r)/2),right=query(a,b,2*k+2,(l+r)/2,r);
        return Data(min(left.minX,right.minX),max(left.maxX,right.maxX));
    }

    void show(){int i;rep(i,nn-1)printf("(%d,%d) ",tree[i+n-1].minX,tree[i+n-1].maxX);printf("(%d,%d)\n",tree[i+n-1].minX,tree[i+n-1].maxX);}
}SegT;

typedef pair<int,int> p;

int l,q;
vector<p> ipt;

int main(){
    int i,j;
    Data left,right;
    scanf("%d%d",&l,&q);
    CC xs(0,l+2);
    xs.add(0);xs.add(l);
    while(q--){
        scanf("%d%d",&i,&j);
        ipt.push_back(p(i,j));
        xs.add(j);
    }
    SegT tree(xs.size());
    //rep(i,l+1)printf("%d->%d\n",i,xs.x2Id(i));
    //tree.show();
    tree.update(xs(0),1);tree.update(xs(l),1);
    for(auto& tmp:ipt){
        if(tmp.first==1){
            tree.update(xs(tmp.second),1);
            //printf("%d->%d\n",tmp.second,xs.x2Id(tmp.second));
            //tree.show();
        }else{
            left=tree.query(xs(0),xs(tmp.second),0,0,NIL);
            right=tree.query(xs(tmp.second),xs.size(),0,0,NIL);
            //printf("%d %d\n",xs.id2X(right.minX),xs.id2X(left.maxX));
            printf("%d\n",xs[right.minX]-xs[left.maxX]);
        }
    }
    return 0;
}