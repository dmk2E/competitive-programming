/*アルゴリズムと工夫点(Paired Information（★5）/CPU: 58 ms Memory: 18632 KB  Length: 3337 B)
数列Aの各要素を頂点とみなし，Ai+Aj=Vの時，AiとAjに重みVの辺をつけ足していくグラフの問題と捉える．
矛盾するような入力は与えられないから，このグラフは必ず木となり，2つの頂点Ai,Ajが互いに連結である時，Aiの値が決まると必ずAjの値も決まる．連結判定はUnion-Find木で行う．
T=1のクエリの答えは再帰を用いたDFSで解ける...がこのままだとTLEしてしまう．
このグラフの性質として，ある2頂点間の関係は，新たな2頂点間の関係が判明しても変わらない．
また，Aiの値が1変化すると，他のAjの値は±1だけしか変化しないという性質がある(←実験等で気づくべきだった)．
よって，
1.T=1のクエリで得られた関係性を先読みして，グラフをまず完成させる．
2.A0=0,A0=1の2パターンの場合の各頂点の値を調べ，差分を取ることで答えを得ることができる．
※キーワード:「クエリ先読み」 「全てのクエリを一旦見て座標圧縮」や「特定のクエリの先に処理する」等，バリエーションは様々
※今回は問題の制約上，A1~ANまでの関係性は最終的には隣接になる．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

typedef class UnionFindTree{
    vector<int> par,rank;
public:
    UnionFindTree(int size){
        int i;
        rank=vector<int>(size,0);
        rep(i,size){
            par.push_back(i);
        }
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int x,int y){
        x=root(x);
        y=root(y);
        if(x==y)return ;
        if(rank[x]<rank[y])
            par[x]=y;
        else{
            par[y]=x;
            if(rank[x]==rank[y])rank[x]++;
        }
    }

    bool isSame(int x,int y){
        return root(x)==root(y);
    }
}UF;

typedef pair<int,int> p;

int n,q;

int main(){
    int i;
    scanf("%d%d",&n,&q);
    vector<vector<int> > query(q,vector<int>(4));
    vector<vector<p> > adj(n,vector<p>(0));
    UF tree(n);
    const int NIL=-1;
    vector<ll> a0(n,NIL),a1(n,NIL);
    auto dfs=[&](auto& f,int par,int now,ll v,vector<ll>& a)->void{
        int i,vv;
        a[now]=v;
        rep(i,adj[now].size()){
            if(a[adj[now][i].first]==NIL){//問題の都合上，木ではない場合があるため，「adj[now][i].first!=NIL」という条件は使えない
                //printf("%d:%lld\n",adj[now][i].first,(ll)adj[now][i].second-v);
                f(f,now,adj[now][i].first,(ll)adj[now][i].second-v,a);
            }
        }
    };
    // auto bfs=[&](int now,ll v,vector<ll>& a){
    //     int i;
    //     queue<ll> que;
    //     a[now]=v;
    //     que.push(now);
    //     while(que.size()){
    //         now=que.front();que.pop();
    //         rep(i,adj[now].size()){
    //             if(a[adj[now][i].first]==NIL){
    //                 a[adj[now][i].first]=adj[now][i].second-a[now];
    //                 que.push(adj[now][i].first);
    //             }
    //         }
    //     }
    // };
    rep(i,q){
        scanf("%d%d%d%d",&query[i][0],&query[i][1],&query[i][2],&query[i][3]);
        query[i][1]--;query[i][2]--;
        if(query[i][0]==0){
            adj[query[i][1]].push_back(p(query[i][2],query[i][3]));
            adj[query[i][2]].push_back(p(query[i][1],query[i][3]));
            tree.unite(query[i][1],query[i][2]);
        }
    }
    rep(i,n)if(tree.root(i)==i){
        //printf("root:%d\n",i);
        //bfs(i,0,a0);
        dfs(dfs,NIL,i,0,a0);
    }
    rep(i,n)if(tree.root(i)==i){
        //printf("root:%d\n",i);
        //bfs(i,1,a1);
        dfs(dfs,NIL,i,1,a1);
    }
    //rep(i,n)printf("a0(%d):%lld a1(%d):%lld\n",i,a0[i],i,a1[i]);
    ll dv;
    tree=UF(n);
    rep(i,q){
        if(query[i][0]==0)
            tree.unite(query[i][1],query[i][2]);
        else{
            if(!tree.isSame(query[i][1],query[i][2]))puts("Ambiguous");
            else{
                dv=query[i][3]-a0[query[i][1]];
                if((dv>0?1:-1)==a1[query[i][1]]-a0[query[i][1]])
                    printf("%lld\n",a0[query[i][2]]+(a1[query[i][2]]-a0[query[i][2]])*abs(dv));
                else
                    printf("%lld\n",a0[query[i][2]]+(a0[query[i][2]]-a1[query[i][2]])*abs(dv));
                //printf("a0(%d):%lld a1(%d):%lld dv:%lld\n",query[i][1],a0[query[i][1]],query[i][1],a1[query[i][1]],dv);
            }
        }
    }
    return 0;
}