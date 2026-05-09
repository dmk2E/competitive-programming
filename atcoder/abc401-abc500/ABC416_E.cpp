/*アルゴリズムと工夫点(Development/CPU: 458 ms Memory: 5920 KB  Length: 1517 B)
超頂点+ワーシャル・フロイド法の応用 で解く．
空港が追加された時，空港が存在する全頂点同士を辺で繋いでいると，O(N^2)程かかってしまう．
そこで，空港を経由する用の``超頂点''を用意する．
また，新たな辺の追加時は，その辺を経由する場合の経路長を考えればよいため，最短距離の更新はO(N^2)で可能となる．
よって最悪計算量は，O(N^(3)+M+Q*N^(2))<10^8 となり間に合う．
※超頂点とは，辺の総本数を減らす目的で設置される，``中継地点''の役割をもつ頂点のこと
※無向グラフであったとしても，向きによって重みを適切に設定し，処理をしやすくできる
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m,t,q;

int main(){
    int i,j,k;
    ll sum=0;
    scanf("%d%d",&n,&m);
    const ll INF=(1e15);
    vector<vector<ll> > dist(n+1,vector<ll>(n+1,INF));
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        dist[i][j]=dist[j][i]=min(dist[i][j],(ll)k);
    }
    scanf("%d%d",&k,&t);
    while(k--){
        scanf("%d",&i);
        dist[i][0]=0;
        dist[0][i]=t;
    }
    // ワーシャル・フロイド法で前計算
    rep(i,n+1)dist[i][i]=0;
    rep(i,n+1)rep(j,n+1)rep(k,n+1)dist[j][k]=min(dist[j][k],dist[j][i]+dist[i][k]);
    rep(i,n)rep(j,n)sum+=(dist[i+1][j+1]==INF?0:dist[i+1][j+1]);
    scanf("%d",&q);
    auto update=[&](int x,int y,int cost)->void{
        int i,j;
        rep(i,n+1)rep(j,n+1){
            if(i>0&&j>0)sum-=dist[i][j]==INF?0:dist[i][j];
            dist[i][j]=min(dist[i][j],dist[i][x]+cost+dist[y][j]);
            if(i>0&&j>0)sum+=dist[i][j]==INF?0:dist[i][j];
        }
    };
    while(q--){
        scanf("%d",&i);
        if(i==1){
            int x,y,cost;
            scanf("%d%d%d",&x,&y,&cost);
            update(x,y,cost);
            update(y,x,cost);
        }else if(i==2){
            scanf("%d",&i);
            update(i,0,0);
            update(0,i,t);
        }else
            printf("%lld\n",sum);
    }
    return 0;
}