/*アルゴリズムと工夫点(Unicyclic Components/CPU: 41 ms Memory: 6996 KB  Length: 1301 B)
Union-Find木で，連結成分毎に頂点と辺の数をそれぞれ記録して，最後に判定すればよい．
※初見4完できた!嬉しい!
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

typedef class UnionFind{
    int par[MAX_N],rank[MAX_N],node[MAX_N],edge[MAX_N];
public:
    UnionFind(int nn){
        int i;
        rep(i,nn){
            par[i]=i;
            edge[i]=rank[i]=0;
            node[i]=1;
        }
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x){edge[y]++;return ;}
        if(rank[y]<rank[x]){
            par[y]=x;
            node[x]+=node[y];
            edge[x]++;
        }else{
            par[x]=y;
            edge[y]++;
            node[y]+=node[x];
            if(par[y]==par[x])rank[y]++;
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    bool judge(int n){
        int i;
        rep(i,n)
            if(root(i)==i&&node[i]!=edge[i])
                return false;
        return true;
    }
}UF;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    UF tree(n);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        tree.unite(i,j);
    }
    printf("%s\n",tree.judge(n)?"Yes":"No");
    return 0;
}