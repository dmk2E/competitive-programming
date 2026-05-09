/*アルゴリズムと工夫点(Double Sum/CPU: 162 ms Memory: 32424 KB  Length: 1612 B)
「平面走査」というアルゴリズムを用いれば、セグ木で解ける。
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 400000
#define NIL -1
using namespace std;

typedef struct data{
    int cnt;
    long long sum;

    data(int ccnt=0,long long ssum=0):cnt(ccnt),sum(ssum){}
}Data;

typedef class SegTree{
    int n;
    Data tree[4*MAX_N];
public:
    SegTree(int nn){
        n=1;
        while(n<nn)n*=2;
        int i;
        rep(i,nn)tree[i+n-1]=Data();
    }

    void update(int k,int a){
        k+=n-1;
        tree[k].sum=a;
        tree[k].cnt=1;
        while(k>0){
            k=(k-1)/2;
            tree[k].sum=tree[2*k+1].sum+tree[2*k+2].sum;
            tree[k].cnt=tree[2*k+1].cnt+tree[2*k+2].cnt;
        }
    }

    Data query(int a,int b,int k,int l,int r){
        if(r==NIL)r=n;
        if(b<=l||r<=a)return Data();
        if(a<=l&&r<=b)return tree[k];
        Data ll=query(a,b,2*k+1,l,(l+r)/2),rr=query(a,b,2*k+2,(l+r)/2,r);
        return Data(ll.cnt+rr.cnt,ll.sum+rr.sum);
    }
}SegT;

typedef pair<int,int> p;

int n;
vector<p> a;

int main(){
    int i,j;
    long long ans=0;
    Data temp;
    scanf("%d",&n);
    SegT tree(n);
    rep(i,n){
        scanf("%d",&j);
        a.push_back(p(j,i));
    }
    sort(a.begin(),a.end());
    rep(i,n){
        tree.update(a[i].second,a[i].first);
        temp=tree.query(0,a[i].second,0,0,NIL);
        //printf("%d %d %lld %d\n",a[i].first,a[i].second,temp.sum,temp.cnt);
        ans+=(long long)temp.cnt*a[i].first-temp.sum;
    }
    printf("%lld\n",ans);
    return 0;
}