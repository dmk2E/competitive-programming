/*アルゴリズムと工夫点(Pair Annihilation/CPU: 48 ms Memory: 14600 KB  Length: 982 B)
「辺を通る回数を最小化」する問題と捉え，考察すると，ボトムアップに電子と陽子を回収していく問題になる．
実装はDFSで行い，最悪計算量は O(N)<10^6 となり十分高速．
※考察力が問われる問題．このような問題も解けるようになりたい...
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Edge{
    int to,cost;

    Edge(int tto=0,int ccost=0):to(tto),cost(ccost){}
};

int n;

int main(){
    int i,j,k,ii;
    const int NIL=-1;
    scanf("%d",&n);
    vector<int> x(n);
    vector<vector<Edge> > adj(n);
    rep(i,n)scanf("%d",&x[i]);
    rep(ii,n-1){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        adj[i].push_back(Edge(j,k));
        adj[j].push_back(Edge(i,k));
    }
    auto dfs=[&](auto& func,int last,int now,ll& sum)->int{// 陽電子と電子の個数を返す
        int i;
        for(Edge e:adj[now])if(e.to!=last){
            sum+=((ll)e.cost)*abs(func(func,now,e.to,sum));
            x[now]+=x[e.to];
        }
        return x[now];
    };
    ll sum=0;
    dfs(dfs,NIL,0,sum);
    printf("%lld\n",sum);
    return 0;
}