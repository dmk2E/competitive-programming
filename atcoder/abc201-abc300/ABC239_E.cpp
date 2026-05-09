/*アルゴリズムと工夫点(Subtree K-th Max/CPU: 122 ms Memory: 42892 KB  Length: 1105 B)
前処理で，各頂点を根としたときの部分木に含まれる上位20個の整数Xを求めて置き，各クエリに答えればよい．
id2X[i][j]:頂点番号iの頂点を根としたときの部分木に含まれる，j+1番目に大きい整数X
とし，このテーブルを木DPで求める．
ある頂点vと繋がっている頂点uiについて，id2X[ui]をそれぞれ参照し，全体で上位20個の整数を取り出し，id2X[v]を更新する．
id2X[i].size()<=MAX_K=20 となるから，全体として，最悪計算量O(MAX_K*N*log2(MAX_K*N)+Q)<10^8 となり，間に合う．
※初見5完! 
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_K 20
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<int> x(n);
    rep(i,n)scanf("%d",&x[i]);
    vector<vector<int> > adj(n),id2X(n);
    while(--n){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    auto dfs=[&](auto& f,int now,int par)->void{
        int i,j;
        priority_queue<int> PQ;
        PQ.push(x[now]);
        rep(i,adj[now].size()){
            if(adj[now][i]==par)continue;
            f(f,adj[now][i],now);
            rep(j,id2X[adj[now][i]].size())PQ.push(id2X[adj[now][i]][j]);
        }
        i=0;
        while(i<MAX_K&&PQ.size()){
            id2X[now].push_back(PQ.top());PQ.pop();
            i++;
        }
    };
    const int NIL=-1;
    dfs(dfs,0,NIL);
    while(q--){
        scanf("%d%d",&i,&j);
        printf("%d\n",id2X[i-1][j-1]);
    }
    return 0;
}