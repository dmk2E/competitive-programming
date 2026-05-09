/*アルゴリズムと工夫点(Family and Insurance/CPU: 141 ms Memory: 24004 KB  Length: 935 B)
優先度付きキュー+多始点BFSで解く．
人を頂点，親->子にのみ辺が張られた有向グラフを考える．
すると，保険の加入者xiを始点とし，そこから最大で距離yiだけ先にいる頂点はその保険の補償対象者である．
そこで，ある地点から伝播していく保険の距離の残量の最大値を，各頂点について求めればよい．
最悪計算量は，O((N+M)*log2(N+M))<10^7 となり高速．
※公式解説は，DAGであることを利用したDPで解いていた．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,m;

int main(){
    int i,j,ans=0;
    scanf("%d%d",&n,&m);
    const int NIL=-1;
    vector<vector<int> > to(n);
    rep(i,n-1){
        scanf("%d",&j);
        to[j-1].push_back(i+1); 
    }
    vector<bool> vis(n,false);
    priority_queue<P> pq;
    while(m--){
        scanf("%d%d",&i,&j);
        pq.push(P(j,i-1));
    }
    while(pq.size()){
        P now;
        do{
            now=pq.top();pq.pop();
        }while(pq.size()&&vis[now.second]);
        if(vis[now.second])break;
        vis[now.second]=true;
        ans++;
        for(int nxt:to[now.second])if(vis[nxt]==false&&now.first>0)pq.push(P(now.first-1,nxt));
    }
    printf("%d\n",ans);
    return 0;
}