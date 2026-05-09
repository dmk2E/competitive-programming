/*アルゴリズムと工夫点(Permute K times 2/CPU:  ms Memory:  KB  Length:  B)
ダブリングの応用問題．
Pi=P(Pi) の条件を添え字に着目して図にしてみるとfunctional-graph になるが，k回操作した後の値は，このグラフを2^k辿った先になる．
しかし，k<=10^(18) となるから，そのまま通常のダブリングをするだけでは，メモリが足らなくなる．
functional-graph では，閉路が存在するため，この閉路の長さCとすると，2^(k)%C 回辿った先が分かればよい．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll k;

int power(int x,ll a,const int& MOD){
    if(a==0)return 1;
    int res=power((int)(((ll)x*x)%MOD),a/2,MOD);
    if(a%2==1)res=(int)(((ll)res*x)%MOD);
    return res;
}

int main(){
    int i,j;
    scanf("%d%lld",&n,&k);
    const int MAX=60;
    vector<vector<int> > adj(n),dp(MAX+1,vector<int>(n));
    rep(i,n){
        scanf("%d",&dp[0][i]);
        dp[0][i]--;
        adj[i].push_back(dp[0][i]);
    }
    rep(i,MAX)rep(j,n)dp[i+1][j]=dp[i][dp[i][j]];
    //rep(i,3){rep(j,n-1)printf("%d ",dp[i][j]+1);printf("%d\n",dp[i][j]+1);}
    const int NIL=-1;
    vector<int> color(n,NIL),cycle,visited(n,NIL);
    auto bfs=[&](int now,int c)->int{
        int i,start=now;
        queue<int> que;
        que.push(now);
        visited[now]=0;
        color[now]=c;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(visited[adj[now][i]]==NIL){
                    visited[adj[now][i]]=visited[now]+1;
                    color[adj[now][i]]=c;
                    que.push(adj[now][i]);
                }else if(adj[now][i]==start){
                    return visited[now]+1;
                }
            }
        }
        return NIL;
    };
    j=0;
    rep(i,n){
        if(color[i]==NIL){
            cycle.push_back(bfs(i,j));
            j++;
        }
    }
    //rep(i,cycle.size())printf("%d ",cycle[i]);puts("");
    auto cal=[&](int now,int val)->int{
        int i=0;
        while(val>0){
            if(val&1)now=dp[i][now];
            i++;
            val/=2;
        }
        return now;
    };
    rep(i,n-1)printf("%d ",cal(i,power(2,k,cycle[color[i]]))+1);
    printf("%d\n",cal(i,power(2,k,cycle[color[i]]))+1);
    return 0;
}