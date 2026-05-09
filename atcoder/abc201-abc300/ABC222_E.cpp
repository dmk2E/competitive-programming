/*アルゴリズムと工夫点(Red and Blue Tree/CPU: 216 ms Memory: 4760 KB  Length: 1579 B)
各辺を何回通るかをDFSで求め，C=(c1,c2,...,cn-1)という列で表されるとする．
すると，S=c1+c2+...+cn-1とすると，R+B=Sとなるから，「2*R=S+Kを満たすRとなるときの，Cの選び方の数を求めよ」という問題になる．
これは部分和問題のDPで解ける．
※R+B=Sという不変量に気づけなかった...RとBは完全に独立でないことから，Rだけ考えればよいということにすぐ気づくことができるようになりたい．
※負の数の余りを求めるコードはバグの原因となることがあることに注意．
※辺を通る回数が「0」となる辺をなかったことにしてしまっていたため，そのことに気づくのにめちゃくちゃ時間がかかった...
*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 1000
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

typedef struct edge{
    int to,id;

    edge(int tto=0,int iid=0):to(tto),id(iid){}
}Edge;

int n,m,k;
vector<int> a,cnt;
vector<Edge> adj[MAX_N];

bool dfs(int par,int now,int& goal){
    int i;
    if(now==goal)return true;
    rep(i,adj[now].size()){
        if(adj[now][i].to!=par&&dfs(now,adj[now][i].to,goal)){
            cnt[adj[now][i].id]++;
            return true;
        }
    }
    return false;
}

int main(){
    int i,j,ii;
    scanf("%d%d%d",&n,&m,&k);
    a=vector<int>(m);
    rep(i,m){
        scanf("%d",&a[i]);
        a[i]--;
    }
    rep(i,n-1){
        scanf("%d%d",&ii,&j);
        ii--;j--;
        adj[ii].push_back(Edge(j,i));
        adj[j].push_back(Edge(ii,i));
    }
    cnt=vector<int>(n-1,0);
    rep(i,m-1)
        dfs(-1,a[i],a[i+1]);
    ii=0;   //ii=R+B
    rep(i,n-1)
        ii+=cnt[i];
    vector<int> last(ii+1,0);
    last[0]=1;
    rep(i,n-1){
        vector<int> now(ii+1,0);
        for(j=0;j<=ii;j++){
            now[j]=(int)(((ll)now[j]+last[j])%MOD);
            now[j+cnt[i]]=(int)(((ll)now[j+cnt[i]]+last[j])%MOD);
        }
        swap(last,now);
    }
    //printf("sum:%d\n",ii);for(p x:last)printf("(%d,%d)\n",x.first,x.second);
    printf("%d\n",(ii+k>=0&&(ii+k)%2==0&&ii+k<=2*ii)?last[(ii+k)/2]:0);
    return 0;
}
    // map<int,int> last;//(値,数) DPを連想配列を用いて求めるver(CPU:82ms で今回はこっちの方が早い)
    // last[0]=1;
    // rep(i,n-1){
    //     map<int,int> now;
    //     for(p x:last){
    //         now[x.first]=(int)(((ll)now[x.first]+x.second)%MOD);
    //         now[x.first+cnt[i]]=(int)(((ll)now[x.first+cnt[i]]+x.second)%MOD);
    //     }
    //     swap(last,now);
    // }