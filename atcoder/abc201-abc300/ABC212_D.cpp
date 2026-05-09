/*アルゴリズムと工夫点(Querying Multiset/CPU: 79 ms Memory: 22704 KB  Length: 2923 B)
やりたい事は，値の追加と区間更新と，区間最小値探索であるから，セグ木で解ける．
ただ，セグ木の各節点は，(配列上の添え字,現在の値)の二つの値を持つようにすると楽．
最悪計算量は O(Q*log2(Q))<10^7 となり，十分高速．
※初見4完達成!嬉しい!
※想定解では，(配列上の添え字,現在の値)の情報さえあればよいから，それを利用して優先度付きキューと累積和の考えで解ける．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_Q (int)(2e5)
#define MAX_MIN (long long)((2e14)+1)
#define NIL -1
using namespace std;

typedef struct value{
    int id;
    long long x;

    value(int iid=NIL,long long xx=MAX_MIN):id(iid),x(xx){}

    bool operator<(const value& k){
        return x<k.x;
    }
}Value;

typedef struct data{
    Value d;
    long long delay;

    data(long long ddelay=0):delay(ddelay){
        d=value();
    }


}Data;

typedef class SegmentTree{
    int n;
    Data tree[4*MAX_Q];
public:
    SegmentTree(int nn){
        int i;
        n=1;
        while(n<nn)n*=2;
    }

    void update(int k,long long a){
        tree[k+n-1].d.id=k;
        k+=n-1;
        tree[k].d.x=a;
        while(k>0){
            k=(k-1)/2;
            tree[k].d=tree[2*k+1].d<tree[2*k+2].d?tree[2*k+1].d:tree[2*k+2].d;
        }
    }

    void eval(int k,int l,int r){
        if(tree[k].delay!=0){
            tree[k].d.x+=tree[k].delay;
            if(tree[k].d.x>MAX_MIN)
                tree[k].d.x=MAX_MIN;
            if(r-l>1){
                tree[2*k+1].delay+=tree[k].delay;
                tree[2*k+2].delay+=tree[k].delay;
            }
            tree[k].delay=0;
        }
    }

    void mapping(int a,int b,int k,int l,int r,long long dx){
        if(r==NIL)r=n;
        eval(k,l,r);
        if(b<=l||r<=a)return ;
        if(a<=l&&r<=b){
            tree[k].delay+=dx;
            eval(k,l,r);
        }else{
            mapping(a,b,2*k+1,l,(l+r)/2,dx);
            mapping(a,b,2*k+2,(l+r)/2,r,dx);
            tree[k].d=tree[2*k+1].d<tree[2*k+2].d?tree[2*k+1].d:tree[2*k+2].d;
        }
    }

    Value query(int a,int b,int k,int l,int r){
        if(r==NIL)r=n;
        if(b<=l||r<=a)return Value();
        eval(k,l,r);
        if(a<=l&&r<=b)return tree[k].d;
        Value ll=query(a,b,2*k+1,l,(l+r)/2),rr=query(a,b,2*k+2,(l+r)/2,r);
        return ll<rr?ll:rr;
    }

    void show(int nn){
        int i;
        printf("tree:");rep(i,nn)printf("%lld ",query(i,i+1,0,0,NIL).x);puts("");
    }
}SegT;

int q;

int main(){
    int i,nxt=0;
    Value min;
    scanf("%d",&q);
    SegT tree(q);
    while(q--){
        scanf("%d",&i);
        switch(i){
            case 1:
                scanf("%d",&i);
                tree.update(nxt++,i);
                //tree.show(nxt);
                break;
            case 2:
                scanf("%d",&i);
                tree.mapping(0,nxt,0,0,NIL,i);
                //tree.show(nxt);
                break;
            default:
                min=tree.query(0,nxt,0,0,NIL);
                printf("%lld\n",min.x);
                tree.mapping(min.id,min.id+1,0,0,NIL,MAX_MIN);
                //printf("j:%d\n",min.id);tree.show(nxt);
                break;
        }
    }
    return 0;
}