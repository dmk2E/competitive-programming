/*アルゴリズムと工夫点(Intersecting Intervals/CPU: 1428 ms Memory: 128552 KB  Length: 3077 B)
座標圧縮して，配列に保持し，x座標の昇順に[l,r]の区間を見ていく．[l,r]の中で既に出てきた区間の数をセグ木で保持し，順に加算していく．見た後は，その区間に+1する．
そうすることで，最悪計算量はO(N*log2(12*N))<10^7 となり，高速．
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_NN 3000000
#define MAX_N 12000000
#define NIL -1
using namespace std;

typedef pair<int,int> p;

typedef struct data{
    int x,delay;

    data(int xx=NIL,int ddelay=0):x(xx),delay(ddelay){}
}Data;

typedef class SegTree{
    int n,nn;
    Data tree[MAX_N];
    //vector<Data> tree;
public:
    SegTree(int nnn=0){
        nn=nnn;
        n=1;
        while(n<nn)n*=2;
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

    void update(int k,int a){
        k+=n-1;
        tree[k].x=a;
        while(k>0){
            k=(k-1)/2;
            tree[k].x=max(tree[2*k+1].x,tree[2*k+2].x);
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
        tree[k].x=max(tree[2*k+1].x,tree[2*k+2].x);
    }

    int query(int a,int b,int k,int l,int r){
        if(r==-1)r=n;
        if(b<=l||r<=a)return NIL;
        eval(k,l,r);
        if(a<=l&&r<=b)return tree[k].x;
        return max(query(a,b,2*k+1,l,(l+r)/2),query(a,b,2*k+2,(l+r)/2,r));
    }

    void show(){int i;rep(i,nn-1)printf("%d ",tree[i+n-1].x);printf("%d\n",tree[i+n-1].x);}
}SegT;

int n,i2A[MAX_N+1],nn;
priority_queue<int> PQ;
priority_queue<p> in;

int a2I(int aa){
    int left=0,right=nn,mid;
    while(left<right){
        mid=(left+right)/2;
        if(i2A[mid]<aa)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i,j,k;
    long long cnt=0;
    p now;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d%d",&j,&k);
        PQ.push(-j);PQ.push(-k);
        if(j-1>=0)
            PQ.push(-j+1);
        if(k-1>=0)
            PQ.push(-k+1);
        PQ.push(-j-1);
        PQ.push(-k-1);
        in.push(p(-j,k));
    }
    i=0;
    j=-PQ.top();PQ.pop();
    i2A[i++]=j;
    while(PQ.size()){
        j=-PQ.top();PQ.pop();
        if(i2A[i-1]!=j)
            i2A[i++]=j;
    }
    nn=i;
    SegT tree(nn);
    //for(pair<int,int> x:a2I){printf("%d %d\n",x.first,x.second);}
    //rep(i,nn)printf("%d ",i2A[i]);puts("");
    rep(i,nn+1)
        tree.update(i,0);
    //tree.show();
    while(in.size()){
        now=in.top();in.pop();
        now.first*=-1;
        //printf("%d %d\n",a2I(now.first),a2I(now.second));
        cnt+=tree.query(a2I(now.first),a2I(now.second)+1,0,0,-1);
        tree.mapping(a2I(now.first),a2I(now.second)+1,0,0,-1,1);
        //tree.show();
    }
    printf("%lld\n",cnt);
    return 0;
}