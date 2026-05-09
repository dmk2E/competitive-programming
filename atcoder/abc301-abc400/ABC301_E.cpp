/*アルゴリズムと工夫点(Pac-Takahashi/CPU: 605 ms Memory: 126792 KB  Length: 3216 B)
始点と終点とお菓子の位置を頂点とする，無向重み付きグラフにおける，最短経路問題に帰着させる．
頂点数Nとすると，各頂点間の全点対最短経路問題は，O(NHW)<10^6 で解くことができ，それにより隣接行列を作成できる．
そうすると，既に訪れたお菓子の集合Sとし，この時に各頂点に到達する時の最小移動回数を求める，巡回セールスマン問題の一種と捉えることができる．
従って，最悪計算量はO(NHW+N^(2)*2^(N))≒10^8 となり間に合う．
※巡回セールマン問題の一種としてではなく，ダイクストラ法で解こうとしてしまった...
※ビット演算子やシフト演算子が絡む式は必ず優先順位を括弧を使って明示すること．
※NIL=h*w+1 としていたために，11WA となってしまっていた...
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef enum state{
    WALL=-2,
    EMPTY=-1,
}State;

typedef struct data{
    int cost,state,id;

    data(int ccost=0,int sstate=0,int iid=0):cost(ccost),state(sstate),id(iid){}

    bool operator<(const data& k)const{
        return cost==k.cost?(id==k.id?state<k.state:id<k.id):cost<k.cost;
    }
}Data;

typedef pair<int,int> p;

int h,w,t;

int popCount(int state){
    int i=0,cnt=0;
    while(state>=(1<<i)){
        cnt+=(state&(1<<i))>0;
        i++;
    }
    return cnt;
}

int main(){
    int i,j,k,ii;
    char c;
    p tmp;
    scanf("%d%d%d",&h,&w,&t);
    vector<vector<int> > mmap(h,vector<int>(w,EMPTY));
    vector<p> vertex;
    k=1;
    rep(i,h){
        getchar();
        rep(j,w){
            c=getchar();
            if(c=='S'){
                vertex.push_back(p(i,j));
                mmap[i][j]=0;
            }else if(c=='o'){
                mmap[i][j]=k++;
            }else if(c=='#')
                mmap[i][j]=WALL;
            else if(c=='G')
                tmp=p(i,j);
        }
    }
    rep(i,h)rep(j,w){
        if(mmap[i][j]>=1)vertex.push_back(p(i,j));
    }
    vertex.push_back(tmp);
    mmap[tmp.first][tmp.second]=vertex.size()-1;
    //rep(i,h){rep(j,w-1)printf("%2d ",mmap[i][j]);printf("%2d\n",mmap[i][j]);}rep(i,vertex.size())printf("(%d,%d)",vertex[i].first,vertex[i].second);puts("");
    const int MAX_D=4,INF=(int)(1e9);
    vector<vector<int> > adj(vertex.size(),vector<int>(vertex.size(),INF));
    int dy[]={-1,0,1,0},dx[]={0,1,0,-1};
    auto bfs=[&](int id)->void{
        vector<vector<int> > visited(h,vector<int>(w,INF));
        queue<p> que;
        int i,y,x;
        p now;
        que.push(vertex[id]);
        visited[vertex[id].first][vertex[id].second]=0;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=now.first+dy[i];x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]!=WALL&&visited[y][x]==INF){
                    visited[y][x]=visited[now.first][now.second]+1;
                    que.push(p(y,x));
                }
            }
        }
        rep(i,adj[id].size()){
            adj[id][i]=visited[vertex[i].first][vertex[i].second];
        }
    };
    rep(i,vertex.size())bfs(i);
    //rep(i,vertex.size()){rep(j,vertex.size()-1)printf("%d ",adj[i][j]);printf("%d\n",adj[i][j]);}
    const int NIL=(int)(1e9);
    int ans=-1;
    vector<vector<int> > dp(1<<vertex.size(),vector<int>(vertex.size(),NIL));
    dp[1][0]=0;
    rep(i,1<<vertex.size()){
        rep(j,vertex.size()){
            rep(k,vertex.size()){
                if(dp[i][j]+adj[j][k]<dp[i|(1<<k)][k])
                    dp[i|(1<<k)][k]=dp[i][j]+adj[j][k];
            }
        }
    }
    rep(i,1<<vertex.size()){
        //printf("%d\n",dp[i][vertex.size()-1]);
        if(dp[i][vertex.size()-1]<=t&&(j=popCount(i)-2)>ans){
            ans=j;
        }
    }
    printf("%d\n",ans);
    return 0;
}
//より高速化ver(CPU: 234 ms Memory: 34480 KB  Length: 3311 B)
/*
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef enum state{
    WALL=-2,
    EMPTY=-1,
}State;

typedef struct data{
    int cost,state,id;

    data(int ccost=0,int sstate=0,int iid=0):cost(ccost),state(sstate),id(iid){}

    bool operator<(const data& k)const{
        return cost==k.cost?(id==k.id?state<k.state:id<k.id):cost<k.cost;
    }
}Data;

typedef pair<int,int> p;

int h,w,t;

int popCount(int state){
    int i=0,cnt=0;
    while(state>=(1<<i)){
        cnt+=(state&(1<<i))>0;
        i++;
    }
    return cnt;
}

int main(){
    int i,j,k,ii;
    char c;
    p tmp;
    scanf("%d%d%d",&h,&w,&t);
    vector<vector<int> > mmap(h,vector<int>(w,EMPTY));
    vector<p> vertex;
    k=1;
    rep(i,h){
        getchar();
        rep(j,w){
            c=getchar();
            if(c=='S'){
                vertex.push_back(p(i,j));
                mmap[i][j]=0;
            }else if(c=='o'){
                mmap[i][j]=k++;
            }else if(c=='#')
                mmap[i][j]=WALL;
            else if(c=='G')
                tmp=p(i,j);
        }
    }
    rep(i,h)rep(j,w){
        if(mmap[i][j]>=1)vertex.push_back(p(i,j));
    }
    vertex.push_back(tmp);
    mmap[tmp.first][tmp.second]=vertex.size()-1;
    //rep(i,h){rep(j,w-1)printf("%2d ",mmap[i][j]);printf("%2d\n",mmap[i][j]);}rep(i,vertex.size())printf("(%d,%d)",vertex[i].first,vertex[i].second);puts("");
    const int MAX_D=4,INF=(int)(1e9);
    vector<vector<int> > adj(vertex.size(),vector<int>(vertex.size(),INF));
    int dy[]={-1,0,1,0},dx[]={0,1,0,-1};
    auto bfs=[&](int id)->void{
        vector<vector<int> > visited(h,vector<int>(w,INF));
        queue<p> que;
        int i,y,x;
        p now;
        que.push(vertex[id]);
        visited[vertex[id].first][vertex[id].second]=0;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=now.first+dy[i];x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]!=WALL&&visited[y][x]==INF){
                    visited[y][x]=visited[now.first][now.second]+1;
                    que.push(p(y,x));
                }
            }
        }
        rep(i,adj[id].size()){
            adj[id][i]=visited[vertex[i].first][vertex[i].second];
        }
    };
    rep(i,vertex.size())bfs(i);
    const int NIL=(int)(1e9);
    int ans=-1;
    vector<vector<int> > dp(1<<(vertex.size()-2),vector<int>(vertex.size(),NIL));
    dp[0][0]=0;
    rep(i,1<<(vertex.size()-2)){
        rep(j,vertex.size()){
            rep(k,vertex.size()){
                if(k==0||k==vertex.size()-1){
                    if(dp[i][j]+adj[j][k]<dp[i][k])
                        dp[i][k]=dp[i][j]+adj[j][k];                    
                }else{
                    if(dp[i][j]+adj[j][k]<dp[i|(1<<(k-1))][k])
                        dp[i|(1<<(k-1))][k]=dp[i][j]+adj[j][k];
                }
            }
        }
    }
    rep(i,1<<(vertex.size()-2)){
        if(dp[i][vertex.size()-1]<=t&&(j=popCount(i))>ans){
            ans=j;   
        }
    }
    printf("%d\n",ans);
    return 0;
}
*/