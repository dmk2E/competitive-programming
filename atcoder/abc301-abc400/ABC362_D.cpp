/*アルゴリズムと工夫点(Shortest Path 3/CPU: 140 ms Memory: 25880 KB  Length: 1436 B)
ダイクストラ法は，生成済みの経路かの判定に必ずbool型のテーブルを用いること．その方が実行時間的にもメモリ的にも性能が高い．
*/
#include<iostream>
#include<vector>
#include<queue>
#define MAX_N (int)(2e5)
#define INFTY (long long)(1e17)
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

typedef pair<int,ll> p;
typedef pair<ll,int> pp;

int n,m;
vector<int> a;
vector<bool> visited(MAX_N,false);
vector<p> adj[MAX_N];
vector<ll> ans;

void dijk(){
    int i,cnt=0;
    pp now;
    priority_queue<pp> PQ;
    ans[0]=a[0];
    PQ.push(pp(-a[0],0));
    while(PQ.size()){
        do{
            now=PQ.top();PQ.pop();
        }while(PQ.size()&&visited[now.second]);
        if(visited[now.second])
            break;
        visited[now.second]=true;
        ans[now.second]=-now.first;
        cnt++;
        // if(cnt==n)
        //     break;
        rep(i,adj[now.second].size()){
            if(visited[adj[now.second][i].first]==false){
                PQ.push(pp(now.first-adj[now.second][i].second,adj[now.second][i].first));
            }
        }
    }
}

int main(){
    int i,j,k;
    scanf("%d%d",&n,&m);
    a=vector<int>(n);
    rep(i,n)
        scanf("%d",&a[i]);
    ans=vector<ll>(n,INFTY);
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        adj[i].push_back(p(j,(ll)a[j]+k));
        adj[j].push_back(p(i,(ll)a[i]+k));
    }
    dijk();
    rep(i,n-2)
        printf("%lld ",ans[i+1]);
    printf("%lld\n",ans[i+1]);
    return 0;
}