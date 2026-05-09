/*アルゴリズムと工夫点(Don't Leave the Spice/CPU: 372 ms Memory: 4304 KB  Length: 1604 B)
動的計画法で解く．
dp[i][j]:1~i+1品目までの中で，香辛料をj[mg]使用した時の価値の最大値とすると，dp[i][j]=max(dp[i-1][j-L],dp[i-1][j-L+1],...,dp[i-1][R]) となる．
区間の最大値を求める作業を高速化するため，セグ木を実装する．最悪計算量は，O(N*(W*log2(W)+W))=O(N*W*log2(W))<10^8 となり，高速．
※初見AC嬉しい!
※スライド最小値はちょくちょく出てくるアルゴリズム．調べといた方がいいかも．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 500
#define MAX_W (int)(1e4)
#define NIL (long long)(-1e18)
using namespace std;

typedef struct SegmentTree{
    int n;
    long long tree[4*MAX_W-1];
    const int rNIL=-1;
public:
    SegmentTree(int nn=0){
        n=1;
        while(n<nn)n*=2;
        int i;
        rep(i,2*n-1)
            tree[i]=NIL;
    }

    void update(int k,long long a){
        k+=n-1;
        tree[k]=a;
        while(k>0){
            k=(k-1)/2;
            tree[k]=max(tree[2*k+1],tree[2*k+2]);
        }
    }

    long long query(int a,int b,int k,int l,int r){
        if(r==rNIL)r=n;
        if(b<=l||r<=a)return NIL;
        if(a<=l&&r<=b)return tree[k];
        return max(query(a,b,2*k+1,l,(l+r)/2),query(a,b,2*k+2,(l+r)/2,r));
    }

    long long get(int k){
        return tree[k+n-1];
    }
}SegT;

int w,n,v;
long long dp[MAX_W+1];

int main(){
    int i,j,k;
    long long temp;
    scanf("%d%d",&w,&n);
    SegT tree(w+1);
    dp[0]=0;
    scanf("%d%d%d",&i,&j,&v);
    for(;i<=j;i++)
        tree.update(i,v);
    tree.update(0,0);
    while(--n){
        //rep(k,w+1)printf("%lld ",tree.get(k)==NIL?-1:tree.get(k));puts("");
        scanf("%d%d%d",&i,&j,&v);
        rep(k,w+1){
            dp[k]=tree.get(k);
            if((temp=tree.query(k-j<0?0:k-j,k-i+1<0?0:k-i+1,0,0,-1))!=NIL)
                dp[k]=max(dp[k],v+temp);
        }
        rep(k,w+1)
            tree.update(k,dp[k]);
    }
    printf("%lld\n",tree.get(w)==NIL?-1:tree.get(w));
    return 0;
}