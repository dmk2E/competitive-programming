/*アルゴリズムと工夫点(Flip Edge/CPU: 298 ms Memory: 30968 KB  Length: 1817 B)
辺の情報に，真偽値をとる状態を付け加え，「あなた」の状態と辺の状態が等しい時のみその辺を渡れる問題と解釈する．
そうすると，各頂点を2状態分だけ増やしたグラフ上でダイクストラ法を適用すればよい．
つまり，拡張ダイクストラ法で解ける．最悪計算量は O((2*N+2*M)*log2(2*N+2*M))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Edge{
    int to;
    bool state;

    Edge(int tto=0,bool sstate=false):to(tto),state(sstate){}
};

struct Data{
    int now;
    bool state;
    ll cost;

    Data(int nnow=0,bool sstate=false,ll ccost=0):now(nnow),state(sstate),cost(ccost){}

    bool operator<(const Data& k)const{
        return cost<k.cost||(cost==k.cost&&(now==k.now?(int)state<(int)k.state:now<k.now));
    }
};

int n,m,x;

int main(){
    int i,j,k;
    scanf("%d%d%d",&n,&m,&x);
    vector<vector<Edge> > adj(n);
    rep(k,m){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(Edge(j,true));
        adj[j].push_back(Edge(i,false));
    }
    const ll NIL=(ll)(1e18);
    auto dijk=[&]()->ll{
        int i,j;
        Data now;
        vector<vector<ll> > vis(n,vector<ll>(2,NIL));
        priority_queue<Data> PQ;
        PQ.push(Data(0,true,0));
        while(PQ.size()){
            do{
                now=PQ.top();PQ.pop();
            }while(PQ.size()&&vis[now.now][now.state]!=NIL);
            //printf("%lld\n",-now.cost);
            vis[now.now][now.state]=-now.cost;
            rep(i,adj[now.now].size()){
                if(adj[now.now][i].state==now.state&&vis[adj[now.now][i].to][now.state]==NIL){
                    PQ.push(Data(adj[now.now][i].to,now.state,now.cost-1));
                }
            }
            if(vis[now.now][!now.state]==NIL){
                PQ.push(Data(now.now,!now.state,now.cost-x));
            }
        }
        return min(vis[n-1][false],vis[n-1][true]);
    };
    printf("%lld\n",dijk());
    return 0;
}