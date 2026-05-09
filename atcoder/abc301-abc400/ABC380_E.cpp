/*アルゴリズムと工夫点(1D Bucket Tool/CPU: 76 ms Memory: 17312 KB  Length: 2458 B)
Union-Find木を用いて，「隣接している同じ色のマスの集合」を管理して解く．
操作1:
各集合のマスは連続しており，集合毎にその連続したマスの左右のマス番号も同時に保持して置けば，新しい色で塗った時に集合の連結を高速で行える．
また，集合毎の要素数も記録して置くことで，色毎のマス数の更新を高速で行える．
操作2:
色毎のマス数を記録したテーブルを参照すればよい．
最悪計算量は O(N+Q*α(N))≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;//[l,r]

typedef class UnionFindTree{
    vector<int> rank,par,cnt,color,count;
    vector<P> lr;
public:
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        cnt=vector<int>(n,1);
        count=vector<int>(n,1);
        int i;
        rep(i,n){
            par.push_back(i);
            color.push_back(i);
            lr.push_back(P(i,i));
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
            cnt[x]+=cnt[y];
            lr[x].first=min(min(lr[x].first,lr[x].second),min(lr[y].first,lr[y].second));
            lr[x].second=max(max(lr[x].first,lr[x].second),max(lr[y].first,lr[y].second));
        }else{
            par[x]=y;
            cnt[y]+=cnt[x];
            lr[y].first=min(min(lr[x].first,lr[x].second),min(lr[y].first,lr[y].second));
            lr[y].second=max(max(lr[x].first,lr[x].second),max(lr[y].first,lr[y].second));
            if(rank[y]==rank[x])rank[y]++;
        }
    }

    bool isSame(int y,int x){
        return root(y)==root(x);
    }

    void paint(int x,int c){
        x=root(x);
        count[color[x]]-=cnt[x];
        color[x]=c;
        count[c]+=cnt[x];
        if(lr[x].first-1>=0&&color[root(lr[x].first-1)]==c){
            unite(lr[x].first-1,x);
        }
        if(lr[x].second+1<(int)rank.size()&&color[root(lr[x].second+1)]==c){
            unite(lr[x].second+1,x);
        }
    }

    int colorCount(int c){
        return count[c];
    }

    void show(){
        int i;
        printf("par:");rep(i,rank.size())printf("%d ",par[i]);puts("");
        printf("cnt:");rep(i,rank.size())printf("%d ",cnt[root(i)]);puts("");
    }
}UF;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    UF tree(n);
    while(q--){
        scanf("%d",&i);
        //tree.show();
        if(i==1){
            scanf("%d%d",&i,&j);
            i--;j--;
            tree.paint(i,j);
        }else{
            scanf("%d",&i);i--;
            printf("%d\n",tree.colorCount(i));
        }
    }
    return 0;
}