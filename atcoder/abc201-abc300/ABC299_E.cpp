/*アルゴリズムと工夫点(Nearest Black Vertex/CPU:  ms Memory:  KB  Length:  B)
全ての頂点から、その頂点を始点とするbfsを行い、あらかじめ任意の2点間の距離を求めておく。最悪計算量はO(N(N+M))≒10^6 となり、十分高速。
その後、白で塗るしかないところを先に塗り、まだ塗ってない頂点を黒く塗った時、条件を満たすか判定することで解く。条件判定の最悪計算量はO(Q*N)≒10^6 となり、十分高速。
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 2000
#define INF (1e9)
#define NIL -1
using namespace std;

typedef struct pair<int,int> p;

int n,m,dist[MAX_N][MAX_N];
vector<int> adj[MAX_N];
p state[MAX_N];

void bfs(int s){
    int now;
    queue<int> que;
    dist[s][s]=0;
    que.push(s);
    while(que.size()){
        now=que.front();que.pop();
        for(int x:adj[now])
            if(dist[s][x]==INF){
                dist[s][x]=dist[s][now]+1;
                que.push(x);
            }
    }
}

void showDist(){
    int i,j;
    rep(i,n){
        rep(j,n)
            printf("%d ",dist[i][j]);
        printf("\n");
    }
}

void showAns(bool ans[]){
    int i;
    rep(i,n)
        printf("%d",ans[i]?0:1);
    puts("");
}

int main(){
    int i,j,k,min,l;
    bool ans[MAX_N];
    scanf("%d%d",&n,&m);
    rep(i,n){
        ans[i]=false;
        rep(j,n)
            dist[i][j]=INF;
    }
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    rep(i,n)
        bfs(i);
    //showDist();
    scanf("%d",&m);
    rep(i,m){
        scanf("%d%d",&state[i].first,&state[i].second);
        state[i].first--;
        rep(j,n)
            if(dist[state[i].first][j]<state[i].second)
                ans[j]=true;
        //showAns(ans);
    }
    rep(i,m){
        min=INF;
        rep(j,n)
            if(ans[j]==false&&min>dist[state[i].first][j]){
                min=dist[state[i].first][j];
            }
        if(min!=state[i].second){
            puts("No");
            return 0;
        }
    }
    printf("Yes\n");
    rep(i,n)
        printf("%d",ans[i]?0:1);
    puts("");
    return 0;
}