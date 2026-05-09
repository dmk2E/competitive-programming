/*アルゴリズムと工夫点(Sum of Maximum Weights/CPU: 32 ms Memory: 5664 KB  Length: 1749 B)
「主客転倒」というアルゴリズムで，重みを固定し，その重みが最大となる2頂点の組み合わせの数を数えていく．
重みの昇順に頂点を連結していけばよく，Union-Find木を用いる．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

typedef class UnionFindTree{
    vector<int> rank,par,cnt;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        cnt=vector<int>(n,1);
        int i;
        rep(i,n)
            par.push_back(i);
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
            cnt[x]+=cnt[y];
        }else{
            par[x]=y;
            cnt[y]+=cnt[x];
            if(rank[y]==rank[x])rank[y]++;
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    int count(int x){
        return cnt[root(x)];
    }

    void show(){
        int i;
        printf("par:");rep(i,rank.size())printf("%d ",par[i]);puts("");
        printf("cnt:");rep(i,rank.size())printf("%d ",cnt[root(i)]);puts("");
    }
}UF;

typedef struct edge{
    int u,v,w;

    edge(int uu=0,int vv=0,int ww=0):u(uu),v(vv),w(ww){}

    bool operator<(const edge& k)const{
        return w<k.w;
    }
}Edge;

int n;

int main(){
    int i;
    long long ans=0;
    scanf("%d",&n);
    UF tree(n);
    vector<Edge> ipt(n-1);
    rep(i,n-1){
        scanf("%d%d%d",&ipt[i].u,&ipt[i].v,&ipt[i].w);
        ipt[i].u--;ipt[i].v--;
    }
    sort(ipt.begin(),ipt.end());
    rep(i,n-1){
        ans+=(long long)tree.count(ipt[i].u)*tree.count(ipt[i].v)*ipt[i].w;
        tree.unite(ipt[i].u,ipt[i].v);
    }
    printf("%lld\n",ans);
    return 0;
}