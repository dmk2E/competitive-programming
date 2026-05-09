/*アルゴリズムと工夫点(Linear Probing/CPU: 71 ms Memory: 23980 KB  Length: 1530 B)
数列Aは別の配列で保持して置く．また，Ai!=-1である連続したAiの列を集合と捉え，Union-Find木で管理する．この時，集合内で最大の頂点番号を保持して置くようにすること．
そうすることで，クエリ1に対してはO(α(N)),クエリ2に対してはO(1)で答えることができる．
従って，最悪計算量はO(Q*α(N)) となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define NIL -1
#define N (1<<20)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par,mx;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        int i;
        rep(i,n){
            par.push_back(i);
            mx.push_back(i);
        }
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return ;
        if(rank[y]<rank[x]){
            par[y]=x;
            mx[x]=max(mx[x],mx[y]);
        }else{
            par[x]=y;
            if(rank[y]==rank[x])rank[y]++;
            mx[y]=max(mx[x],mx[y]);
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    int getMax(int id){
        return mx[root(id)];
    }
}UF;

int q;
vector<ll> a(N,NIL);

int main(){
    int i,j;
    ll x;
    scanf("%d",&q);
    UF tree(N);
    while(q--){
        scanf("%d%lld",&i,&x);
        if(i==1){
            j=(int)(x%N);
            if(a[j]!=NIL)while(a[j=(tree.getMax(j)+1)%N]!=NIL);
            a[j]=x;
            if(j-1>=0&&a[j-1]!=NIL)
                tree.unite(j,j-1);
            if(j+1<N&&a[j+1]!=NIL)
                tree.unite(j,j+1);
        }else
            printf("%lld\n",a[(x%N)]);
    }
    return 0;
}