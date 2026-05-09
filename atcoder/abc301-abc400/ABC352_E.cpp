/*アルゴリズムと工夫点(Clique Connect/CPU: 150 ms Memory: 21200 KB  Length: 1103 B)
k頂点の部分集合が与えられるが,その集合に含まれる頂点が連結になるために必要な辺だけ持っていればよい.
※最小全域木を求めるアルゴリズムとして,プリム法の他にクラスカル法が存在する.クラスカル法は,辺をその重みでソートして,重みの小さい順に辺を追加していく.ただし,既に連結している2頂点間の辺だった場合は追加しない.連結かどう
かはUnion-Find木を用いて判定する.
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
using namespace std;

typedef pair<int,int> p;

int n,m,k,c;
vector<p > adj[MAX_N];

long long prim(){
    int cnt=0;
    long long sum=0;
    p now;
    vector<bool> color(n,true);
    priority_queue<p > PQ;
    PQ.push(p(0,0));
    while(cnt<n&&PQ.size()){
        do{
            now=PQ.top();PQ.pop();
        }while(PQ.size()&&color[now.second]==false);
        if(color[now.second]==false)
            break;
        color[now.second]=false;
        sum-=now.first;
        cnt++;
        for(p x:adj[now.second]){
            if(color[x.first])
                PQ.push(p(-x.second,x.first));
        }
    }
    return cnt==n?sum:-1;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&k,&c,&i);
        i--;
        while(--k){
            scanf("%d",&j);
            j--;
            adj[i].push_back(p(j,c));
            adj[j].push_back(p(i,c));
        }
    }
    printf("%lld\n",prim());
    return 0;
}