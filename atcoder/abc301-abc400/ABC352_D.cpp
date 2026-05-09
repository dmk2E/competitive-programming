/*アルゴリズムと工夫点(Permutation Subsequence/CPU: 54 ms Memory: 12464 KB  Length: 1654 B)
連続した整数列sとする.min(s)を固定した時の,良い添え字列におけるik-i1を出すことを考える.
正の整数xのP上の添え字をa[x]とすると,求める解は,max(a[x],max(a[x,x+k-1)))-mix(a[x],min(a[x,x+k-1)))となるから,a[i,j)の範囲における最大値と最小値が高速に求まればよいから,セグメントツリーで処理する.
最悪計算量はO(N*log2(N))<10^7 となり,十分高速.
※求める答えを出すところで止まってしまい,時間がかかってしまった,,,悔しい.
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
using namespace std;

typedef struct data{
    int max,min;

    data(int mmax=-1,int mmin=MAX_N+1):max(mmax),min(mmin){}
}Data;

typedef class SegTree{
    int n;
    Data tree[5*MAX_N+1];
public:
    SegTree(int nn=0){
        n=1;
        while(n<nn+1)
            n*=2;
    }

    void update(int k,int a){
        k+=n-1;
        tree[k].max=tree[k].min=a;
        while(k>0){
            k=(k-1)/2;
            tree[k].max=max(tree[2*k+1].max,tree[2*k+2].max);
            tree[k].min=min(tree[2*k+1].min,tree[2*k+2].min);
        }
    }

    Data query(int a,int b,int k,int l,int r){
        if(r==-1) r=n;
        if(b<=l||r<=a) return Data();
        if(a<=l&&r<=b) return tree[k];
        Data ll=query(a,b,2*k+1,l,(l+r)/2),rr=query(a,b,2*k+2,(l+r)/2,r);
        //printf("(%d,%d)(%d,%d)\n",ll.min,ll.max,rr.min,rr.max);
        return Data(max(ll.max,rr.max),min(ll.min,rr.min));
    }
}SegT;

int n,k,a[MAX_N+1],p;

int main(){
    int i,mmin=MAX_N+1,j;
    Data temp;
    scanf("%d%d",&n,&k);
    SegT tree(n);
    rep(i,n){
        scanf("%d",&p);
        a[p]=i+1;
    }
    //rep(i,n)printf("i:%d %d\n",i+1,a[i+1]);
    rep(i,n){
        tree.update(i+1,a[i+1]);
    }
    rep(i,n-k+1){//n-k+1
        temp=tree.query(i+2,i+1+k,0,0,-1);
        //temp=tree.query(i+1,i+2,0,0,-1);
        //printf("%d,[%d,%d):min:%d,max:%d\n",a[i+1],i+2,i+1+k,temp.min,temp.max);
        if(mmin>(j=max(a[i+1],temp.max)-min(a[i+1],temp.min)))
            mmin=j;
    }
    printf("%d\n",mmin);
    return 0;
}