/*アルゴリズムと工夫点(航路廃止/CPU: ? ms Memory: ? KB  Length: - B)
多始点BFSをN回繰り返す，貪欲法で解く．
訪問済み頂点を始点とする多始点BFSを行うことで，"ei+(その頂点までの到達時間)"が最小となる頂点iを求め，そこへの移動を最優先で行うことを繰り返すシミュレーションを行えばよい．
最悪計算量は，O(n^2)<10^7 となり高速．
*/
#include<iostream>
#include<cassert>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<list>
#include<algorithm>
// #include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Edge{
    int to,e;

    Edge(int tto=0,int ee=0):to(tto),e(ee){}

    bool operator<(const Edge& k)const{
        return e>k.e;
    }
};

int n;

int main(){
    int i,j,k;
    while(1){
        scanf("%d",&n);
        vector<vector<Edge> > adj(n);
        if(!n)break;
        rep(i,n-1){
            scanf("%d%d",&j,&k);
            j--;
            adj[i+1].push_back(Edge(j,k));
            adj[j].push_back(Edge(i+1,k));
        }
        vector<int> ans;

        auto solve=[&]()->void{
            int now_t=0;
            vector<bool> vis(n,false);
            const int NIL=-1,INF=1000000000;
            auto bfs=[&](){
                queue<int> que;
                vector<int> e(n,INF),par(n,NIL),dist(n,NIL);
                int i;
                rep(i,n)if(vis[i])que.push(i),dist[i]=0;
                while(que.size()){
                    int now=que.front();que.pop();
                    for(Edge edge:adj[now]){
                        if(dist[edge.to]==NIL){
                            que.push(edge.to);
                            e[edge.to]=edge.e;
                            dist[edge.to]=dist[now]+1;
                            par[edge.to]=now;
                        }
                    }
                }
                // eが一番小さいやつを探す
                int min_id=0;
                rep(i,n)if(e[min_id]>e[i])min_id=i;
                if(e[min_id]<now_t+dist[min_id]-1)return false;
                //printf("min_id:%d dist[min_id]=%d e[min_id]=%d \n",min_id,dist[min_id],e[min_id]);
                now_t+=dist[min_id];
                // 経路復元
                i=min_id;
                vector<int> temp;
                vis[0]=true;
                while(dist[i]>0){
                    if(vis[i]==false)temp.push_back(i),vis[i]=true;
                    i=par[i];
                }
                // 解を代入
                rep(i,temp.size())ans.push_back(temp[temp.size()-1-i]);
                return true;
            };
            vis[0]=true;
            while(ans.size()<n-1){
                if(!bfs())return ;
            }
        };
        solve();
        if(ans.size()==n-1){
            puts("yes");
            rep(i,ans.size()-1)printf("%d ",ans[i]+1);
            printf("%d\n",ans[i]+1);
        }else
            puts("no");
    }
    return 0;
}