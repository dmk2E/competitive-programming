/*アルゴリズムと工夫点(Graph Destruction/CPU: 66 ms Memory: 17340 KB  Length: 1405 B)
操作を逆順に行うことを考えると，頂点を順次追加していき，その頂点とそれまでに追加された頂点との間に辺がある場合にその2頂点間を繋ぐという，という操作を繰り返すことになる．
そうすると連結成分の個数は，頂点を追加される毎に+1され，併合が1回起こるたびに-1される．
よって，最悪計算量O(N+M*α(N))<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        int i;
        rep(i,n)
            par.push_back(i);
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    int unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return 0;
        if(rank[y]<rank[x]){
            par[y]=x;
        }else{
            par[x]=y;
            if(rank[y]==rank[x])rank[y]++;
        }
        return 1;
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    void show(){
        int i;
        printf("par:");rep(i,rank.size())printf("%d ",par[i]);puts("");
    }
}UF;

int n,m;

int main(){
    int i,j,now;
    scanf("%d%d",&n,&m);
    vector<vector<int> > adj(n+1,vector<int>(0));
    vector<int> ans;
    while(m--){
        scanf("%d%d",&i,&j);
        adj[i-1].push_back(j-1);
    }
    UF tree(n);
    now=0;
    for(i=n-1;i>=0;i--){
        ans.push_back(now);
        now++;
        rep(j,adj[i].size())now-=tree.unite(i,adj[i][j]);
    }
    rep(i,ans.size())printf("%d\n",ans[ans.size()-1-i]);
    return 0;
}