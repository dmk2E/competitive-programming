/*アルゴリズムと工夫点(Road Reduction/CPU: 153 ms Memory: 22728 KB  Length: 1540 B)
単一始点最短経路問題を考えてみると，頂点1から各頂点への最短経路で用いた辺の数は，必ずN-1本となる．
この木を"ダイクストラ木"とすると，この木を求めればよい．
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
    int id_,to_,cost_;

    Edge(int id=0,int to=0,int cost=0):id_(id),to_(to),cost_(cost){}
};

struct State{
    ll sum_;
    int to_,edge_id_;

    State(ll sum=0,int to=0,int edge_id=0):sum_(sum),to_(to),edge_id_(edge_id){}

    bool operator<(const State& k)const{
        return sum_<k.sum_;
    }
};

int n,m;

int main(){
    int i,j,k,ii;
    scanf("%d%d",&n,&m);
    vector<vector<Edge> > adj(n);
    rep(ii,m){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        adj[i].push_back(Edge(ii+1,j,k));
        adj[j].push_back(Edge(ii+1,i,k));
    }
    const int NIL=-1;
    vector<int> vis(n,NIL);
    // 頂点0にはedge_id=0 とし，他の辺は1-indexedで管理
    auto dijk=[&]()->void{
        State now;
        priority_queue<State> PQ;
        PQ.push(State(0,0,0));
        while(PQ.size()){
            do{
                now=PQ.top();PQ.pop();
            }while(PQ.size()>0&&vis[now.to_]!=NIL);
            //printf("%d(%lld)\n",now.to_,now.sum_);
            if(vis[now.to_]!=NIL)break;
            vis[now.to_]=now.edge_id_;
            for(Edge nxt:adj[now.to_])if(vis[nxt.to_]==NIL)PQ.push(State(now.sum_-nxt.cost_,nxt.to_,nxt.id_));
        }
    };
    dijk();
    rep(i,n-2)printf("%d ",vis[i+1]);
    printf("%d\n",vis[i+1]);
    return 0;
}