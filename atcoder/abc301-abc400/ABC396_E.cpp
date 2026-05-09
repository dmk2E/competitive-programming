/*アルゴリズムと工夫点(Min of Restricted Sum/CPU: 984 ms Memory: 19264 KB  Length: 1467 B)
ビット演算が絡むから，ビット毎に独立に考える．
そのため頂点を30個に拡張し，1または0の値のみをもつ頂点と辺からなるグラフの分析を行う．
・一つの頂点を'0'または'1'に決めると他の頂点全てが決まる（各桁毎に分けているから，1が割り当てられる数が少ない方を選ぶ）
・連結成分ごとに独立
最悪計算量は O(N*log2(N)+M*log2(N))
※'0'と'1'の問題に帰着させることが重要
※最初に決める値が'0'と'1'の内，反転すると，全てに割り当てられる値が反転することを利用して計算量を削減する．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_KETA 30
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,m;

int main(){
    int i,j,k,ii,jj,c,tmp,ttmp;
    scanf("%d%d",&n,&m);
    vector<vector<P> > adj(n);
    while(m--){
        scanf("%d%d%d",&i,&j,&tmp);
        i--;j--;
        adj[i].push_back(P(j,tmp));
        adj[j].push_back(P(i,tmp));
    }
    const int NIL=-1;
    bool is_valid=true;
    vector<int> ans(n,0);
    rep(k,MAX_KETA){
        vector<int> color(n,NIL);
        rep(i,n)if(color[i]==NIL){
            vector<vector<int> > vs(2);
            auto dfs=[&](auto& f,int now,int c)->void{
                if(color[now]!=NIL){
                    if(color[now]!=c)is_valid=false;
                    return ;
                }
                color[now]=c;
                vs[c].push_back(now);
                int i,j;
                rep(i,adj[now].size()){
                    f(f,adj[now][i].first,c^((adj[now][i].second>>k)&1));
                }
            };
            dfs(dfs,i,0);
            if(vs[0].size()<vs[1].size())swap(vs[0],vs[1]);
            for(int v: vs[1])ans[v]|=(1<<k);
        }
    }
    if(is_valid==false){
        puts("-1");
        return 0;
    }
    rep(i,n-1)printf("%d ",ans[i]);printf("%d\n",ans[i]);
    return 0;
}