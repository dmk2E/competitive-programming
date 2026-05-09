/*アルゴリズムと工夫点(Mancala 2/CPU: 377 ms Memory: 16348 KB  Length: 1951 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 400000
#define NIL -1
using namespace std;

typedef struct data{
    long long now,delay;

    data(long long nnow=NIL,long long ddelay=0):now(nnow),delay(ddelay){}
}Data;

int n,m;
Data segT[2*MAX_N-1];

void init(int nn){
    n=1;
    while(n<nn)n*=2;
}

void update(int k,int a){
    k+=n-1;
    segT[k].now=a;
    while(k>0){
        k=(k-1)/2;
        segT[k].now=max(segT[2*k+1].now,segT[2*k+2].now);
    }
}

void eval(int k,int l,int r){
    if(segT[k].delay!=0){
        segT[k].now+=segT[k].delay;
        if(r-l>1){
            segT[2*k+1].delay+=segT[k].delay;
            segT[2*k+2].delay+=segT[k].delay;
        }
        segT[k].delay=0;
    }
}

void mapping(int a,int b,int k,int l,int r,long long x){
    eval(k,l,r);
    if(b<=l||r<=a)return ;
    if(a<=l&&r<=b){
        segT[k].delay+=x;
        eval(k,l,r);
        return ;
    }
    mapping(a,b,2*k+1,l,(l+r)/2,x);mapping(a,b,2*k+2,(l+r)/2,r,x);
    segT[k].now=max(segT[2*k+1].now,segT[2*k+2].now);
}

long long query(int a,int b,int k,int l,int r){
    if(b<=l||r<=a)return NIL;
    eval(k,l,r);
    if(a<=l&&r<=b)return segT[k].now;
    return max(query(a,b,2*k+1,l,(l+r)/2),query(a,b,2*k+2,(l+r)/2,r));
}

int main(){
    int i,nn,j;
    long long cnt;
    scanf("%d%d",&nn,&m);
    init(nn);
    rep(i,nn){
        scanf("%d",&j);
        update(i,j);
    }
    while(m--){
        scanf("%d",&j);
        cnt=query(j,j+1,0,0,n);
        mapping(j,j+1,0,0,n,-cnt);
        mapping(0,nn,0,0,n,cnt/nn);
        cnt%=nn;
        if(j+1+cnt<=nn)
            mapping(j+1,j+1+cnt,0,0,n,1);
        else{
            mapping(j+1,nn,0,0,n,1);
            j=(j+1+cnt)%nn;
            mapping(0,j,0,0,n,1);
        }
    }
    rep(i,nn-1)printf("%lld ",query(i,i+1,0,0,n));printf("%lld\n",query(i,i+1,0,0,n));
    return 0;
}