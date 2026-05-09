/*アルゴリズムと工夫点(Reachability Query/CPU: 132 ms Memory: 6804 KB  Length: 3037 B)
Union-Find木を用いてシミュレーションして解く．
各頂点間の連結状態の把握のため，Union-Find木を利用する．
連結成分ごとの黒い頂点の数，各頂点毎の色をそれぞれ把握した状態でシミュレーションを行う．
最悪計算量は，O(N+Q*α(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    vector<int> rank,par,cnt;
public:
    /// @brief Union-Find 木のコンストラクタ
    /// @param n グラフの頂点数
    UnionFindTree(int n=0){
        rank=vector<int>(n,0);
        par=vector<int>(0);
        cnt=vector<int>(n,1);
        int i;
        rep(i,n)
            par.push_back(i);
    }
    /// @brief 頂点xが属している集合の根（代表頂点）を求める
    /// @param x 対象頂点番号
    /// @return 根の頂点番号
    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }
    /// @brief 2つの頂点それぞれが属する集合の併合を行う
    /// @param y 1つめの頂点番号
    /// @param x 2つめの頂点番号
    /// @return 併合により新たに根となった頂点の番号
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
    /// @brief 2つの頂点が同じ集合か判定
    /// @param y 1つめの頂点番号
    /// @param x 2つめの頂点番号
    /// @return 
    bool isSame(int y,int x){
        return root(y)==root(x);
    }
    /// @brief その頂点が属している集合の数を返す
    /// @param x 頂点番号
    /// @return その頂点が属している集合の数
    int count(int x){
        return cnt[root(x)];
    }
    /// @brief 木の現在の情報出力
    void show(){
        int i;
        printf("par:");rep(i,rank.size())printf("%d ",par[i]);puts("");
        printf("cnt:");rep(i,rank.size())printf("%d ",cnt[root(i)]);puts("");
    }
    /// @brief 頂点数を取得する
    /// @return 木の頂点数
    int size(){
        return rank.size();
    }
}UF;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<bool> is_black(n,false);
    vector<int> count_black(n,0);
    UF tree(n);
    while(q--){
        scanf("%d",&i);
        int v;
        if(i==1){
            int u;
            scanf("%d%d",&u,&v);u--;v--;
            u=tree.root(u);
            v=tree.root(v);
            if(!tree.isSame(u,v)){
                int par=tree.unite(u,v);
                count_black[par]=count_black[u]+count_black[v];
            }
        }else if(i==2){
            scanf("%d",&v);v--;
            if(is_black[v])count_black[tree.root(v)]--;
            else count_black[tree.root(v)]++;
            is_black[v]=!is_black[v];
        }else{
            scanf("%d",&v);v--;
            printf("%s\n",count_black[tree.root(v)]>0?"Yes":"No");
        }
    }
    return 0;
}