/*アルゴリズムと工夫点(Tying Rope/CPU: 54 ms Memory: 7804 KB  Length: 1772 B)
2つのロープa,bを結びつけることを，二つの頂点a,bを連結させると表現する．そのうえで，連結成分に含まれる全てのロープの両端が結ばれていれば，その成分は環となっているといえる．
初見で立てたアルゴリズムは正しかったが，実装が上手くいっておらず，3回程WAしてしまった...．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(2e5)
using namespace std;

typedef class DisjointSet{
    int rank[MAX_N],par[MAX_N],completed[MAX_N],size[MAX_N],n;
public:
    DisjointSet(int ssize){
        int i;
        rep(i,ssize){
            rank[i]=completed[i]=0;
            par[i]=i;
            size[i]=1;
        }
        n=ssize;
    }

    int root(int x){
        return x==par[x]?x:par[x]=root(par[x]);
    }

    void unite(int x,int y){
        x=root(x);
        y=root(y);
        if(x==y)return ;
        if(rank[x]<rank[y]){
            par[x]=y;
            size[y]+=size[x];
            completed[y]+=completed[x];
        }else{
            par[y]=x;
            if(rank[x]==rank[y])
                rank[x]++;
            size[x]+=size[y];
            completed[x]+=completed[y];
        }
    }

    bool isSame(int x,int y){
        return root(x)==root(y);
    }

    void add(int x){
        completed[root(x)]++;
    }

    void count(int& x,int& y){
        int i,cnt=0;
        x=0;
        rep(i,n){
            if(i==root(i)){
                if(size[i]==completed[i])
                    x++;
                cnt++;
            }
        }
        y=cnt-x;
    }
}UF;

int n,m,cnt[MAX_N]={0};

int main(){
    int i,j,k;
    char a,c;
    scanf("%d%d",&n,&m);
    UF tree(n);
    rep(i,m){
        getchar();
        scanf("%d %c %d %c",&j,&a,&k,&c);
        j--;k--;
        tree.unite(j,k);
        cnt[j]++;cnt[k]++;
        //このタイミングでtree.add関数を呼び出すと，WAになってしまう．
    }
    rep(i,n)if(cnt[i]==2)tree.add(i);
    tree.count(i,j);
    printf("%d %d\n",i,j);
    return 0;
}