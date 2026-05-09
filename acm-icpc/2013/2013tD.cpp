/*アルゴリズムと工夫点(沈みゆく島/CPU: 10 ms Memory: 4060 KB  Length: 4116 B)
各島が順番に沈んでいき，島が沈む度にその島に関連する橋が消えるが，その時々で残った島が連結であり続けるための最小費用を求める問題．
ただし，途中で連結不可能になった場合は，橋の建設をストップする．
これは島を頂点，橋を辺とみなした時の，無向重み付きグラフの問題として捉える．
一般的に，辺を削除することは，追加する事より難しい．そこで，逆時系列順で考えてみる．
つまり島が順番に表出し，その度に連結であるための最小費用を求める問題と捉える．
すると，グラフに対して行う操作が，辺の追加のみとなり，求めやすくなる．
連結成分管理は，典型のUnion-Find木で行う．同時に，時間経過と共に，存在する島間の辺を，建設候補の辺として追加していく．
注意点として，途中で連結にすることが不可能になった場合，もう一度各島が独立した状態に戻すこと．
Mの最大値はN^(2)であり，座圧による高速化も含め，最悪計算量は O(N^(3)*log2(N))<10^8 となり，間に合う．
※n<=200 であるため，所々愚直な実装が可能．私の実装では，一度見た辺を消さずに残すことで，実装を楽にしている．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H (int)(1e6)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par,cnt;
public:
    int ans;
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        cnt=vector<int>(n,1);
        int i;
        rep(i,n)par.push_back(i);
        ans=0;
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    int unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return -1;
        if(rank[y]<rank[x]){
            par[y]=x;
            cnt[x]+=cnt[y];
            return x;
        }else{
            par[x]=y;
            cnt[y]+=cnt[x];
            if(rank[y]==rank[x])rank[y]++;
            return y;
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

    int size(){
        return cnt.size();
    }
}UF;

typedef class CordinatedCompression{
    bool initiated;
    vector<int> xs;
public:
    CordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(int x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(int k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    int operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
}CC;

struct Edge{
    int a_,b_,c_;

    Edge(int a=0,int b=0,int c=0):a_(a),b_(b),c_(c){}

    bool operator<(const Edge& k)const{
        return c_<k.c_;
    }
};

int n,m;

int main(){
    int i,j,k;
    UF tree;
    while(1){
        scanf("%d%d",&n,&m);
        if(!(n||m))break;
        vector<int> h(n);
        CC ts;
        rep(i,n){
            scanf("%d",&h[i]);
            ts.add(h[i]);
        }
        vector<vector<int> > time_to_cities(ts.size());
        rep(i,n)time_to_cities[ts(h[i])].push_back(i);
        const int NIL=-1;
        vector<vector<int> > adj(n,vector<int>(n,NIL));
        while(m--){
            scanf("%d%d%d",&i,&j,&k);
            i--;j--;
            adj[i][j]=k;
            adj[j][i]=k;
        }
        // 表出している都市群
        vector<int> st;
        vector<Edge> edges;
        auto kruskal=[&](UF tree)->UF{
            int i,k;
            // クラスカル法本処理
            rep(i,edges.size()){
                if(!tree.isSame(edges[i].a_,edges[i].b_)){
                    k=tree.unite(edges[i].a_,edges[i].b_);
                    tree.ans+=edges[i].c_;
                    if(tree.count(k)==st.size())return tree;
                }
            }
            return UF();
        };
        tree=UF(n);
        for(i=time_to_cities.size()-1;i>=0;i--){
            // その時間で表出してくる島群と，連結済み島群との間の辺を復元
            //printf("time:%d(%d)\n",i,ts[i]);
            for(int id:time_to_cities[i]){
                //printf("%d\n",id);
                for(int c:st){
                    j=min(c,id);
                    k=max(c,id);
                    if(adj[j][k]!=NIL)edges.push_back(Edge(j,k,adj[j][k]));
                }
                st.push_back(id);
            }
            // クラスカル法前処理として，辺を重みの昇順に
            sort(edges.begin(),edges.end());
            UF tmp=kruskal(tree);
            if(tmp.size()>0)swap(tree,tmp);
            else tree=UF(n);
            //printf("edge:%ld\n",edges.size());
            //printf("ans:%d\n",tree.ans);
        }
        printf("%d\n",tree.ans);
    }
    return 0;
}