/*アルゴリズムと工夫点(MST + 1/CPU: 128 ms Memory: 11488 KB  Length: 1861 B)
ある辺を追加した時，それがMSTに含まれるか否かは，クラスカル法における「その辺を追加して閉路ができるか否か」で判定できる．
問題はその判定を行うときの頂点間の連結状態をどう高速に求めるかだが，時系列処理で高速化できる．
つまり，元々ある辺とクエリの辺を同時に扱い，クラスカル法の途中で判定を行う．
元々ある辺ならば，条件を満たす時は追加し，クエリの辺ならば条件を満たすかにかかわらず追加はせず，代わりに解を求めておく．
最悪計算量はソートがボトルネックとなり， O((M+Q)*log2(M+Q))<10^7 となり十分高速．
※このような時系列処理は思いつかなかった...悔しい
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct Edge{
    int id,from,to,c;

    Edge(int ffrom=0,int tto=0,int cc=0,int iid=-1):from(ffrom),to(tto),c(cc),id(iid){}

    bool operator<(const Edge& k)const{
        return c<k.c;
    }
}E;

typedef class UnionFindTree{
    vector<int> par,rank;
public:
    UnionFindTree(int n){
        int i;
        rep(i,n){
            par.push_back(i);
            rank.push_back(0);
        }
    }

    int root(int x){
        return x==par[x]?x:par[x]=root(par[x]);
    }

    void unite(int x,int y){
        x=root(x);
        y=root(y);
        if(x==y)return ;
        if(rank[x]<rank[y])
            par[x]=y;
        else{
            par[y]=x;
            if(rank[x]==rank[y])
                rank[x]++;
        }
    }

    bool isSame(int x,int y){
        x=root(x);
        y=root(y);
        return x==y;
    }
}UF;

int n,m,q;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&m,&q);
    vector<E> edge(m+q);
    const int NIL=-1;
    rep(i,m){
        scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].c);
        edge[i].from--;
        edge[i].to--;
    }
    rep(i,q){
        scanf("%d%d%d",&edge[i+m].from,&edge[i+m].to,&edge[i+m].c);
        edge[i+m].from--;edge[i+m].to--;
        edge[i+m].id=i;
    }
    sort(edge.begin(),edge.end());
    UF tree(n);
    vector<bool> ans(q,false);
    rep(i,edge.size()){
        if(!tree.isSame(edge[i].from,edge[i].to)){
            if(edge[i].id==NIL)
                tree.unite(edge[i].from,edge[i].to);
            else
                ans[edge[i].id]=true;
        }
    }
    rep(i,q)printf("%s\n",ans[i]?"Yes":"No");
    return 0;
}