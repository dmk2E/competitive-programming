/*アルゴリズムと工夫点(Make Bipartite 2/CPU: 81 ms Memory: 30776 KB  Length: 1780 B)
新たに頂点間に辺が増えたところで，頂点が増えないので，「二部グラフではなかったもの」が，「二部グラフであるもの」になることはない．
また，ある塗り方では(i,j)を結んでもダメだが，違う塗り方ではOKになる場合も考慮する必要がある．
つまり<i>違う連結成分同士なら，どの頂点を結んでも良い<ii>同じ成分同士なら，違う色同士なら良い．
ということは，全体から，同じ連結成分で同じ色の辺を引けばよい．
※連結成分の内，一つでも二部グラフにならない場合，グラフGはじょうけんを満たさないため，解は0となることに注意．
※単純グラフは，自己ループと多重辺を持たないだけで，連結であるとは限らない．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef enum state{
    NIL=-1,
    RED=0,
    BLUE=1
}State;

typedef struct edge{
    int to,id;

    edge(int tto=0,int iid=0):to(tto),id(iid){}
}Edge;

int n,m;
vector<vector<Edge> > adj;
vector<State> color;

int main(){
    int i,j,r,b,e;
    ll ans=0;
    scanf("%d%d",&n,&m);
    adj=vector<vector<Edge> >(n,vector<Edge>(0));
    color=vector<State>(n,NIL);
    r=0;
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(Edge(j,r));
        adj[j].push_back(Edge(i,r));
        r++;
    }
    vector<bool> check(r,false);
    auto dfs=[&](auto& f,int now,int c)->int{
        int i,cnt=0,tmp;
        color[now]=(State)c;
        if(c==RED)r++;
        else b++;
        rep(i,adj[now].size()){
            if(color[adj[now][i].to]==NIL){
                cnt++;
                check[adj[now][i].id]=true;
                tmp=f(f,adj[now][i].to,(c+1)%2);
                if(tmp==NIL)return NIL;
                cnt+=tmp;
            }else if(check[adj[now][i].id]==false){
                check[adj[now][i].id]=true;
                cnt++;
                if(color[now]^color[adj[now][i].to]==0)return NIL;
            }
        }
        return cnt;
    };
    e=0;
    rep(i,n){
        if(color[i]==NIL){
            r=b=0;
            j=dfs(dfs,i,RED);
            if(j!=NIL){
                e+=j;
                ans+=(ll)r*(r-1)/2+(ll)b*(b-1)/2;
            }else{
                puts("0");
                return 0;
            }
        }
    }
    printf("%lld\n",(ll)n*(n-1)/2-ans-e);
    return 0;
}