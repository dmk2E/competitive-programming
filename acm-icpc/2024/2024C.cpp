#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
#define MAX_D 6
#define MAX 3000
#define INFTY (int)(1e8)
using namespace std;
typedef long long ll;

typedef pair<int,int> p;

int n,dy[MAX_D]={-1,0,1,0,-1,1},dx[MAX_D]={0,1,0,-1,1,-1};

int bfs(int x,int y){
    int i,xx,yy;
    p now;
    vector<vector<int> > visited=vector<vector<int> >(MAX+1,vector<int>(MAX+1,INFTY));
    queue<p> que;
    visited[1000][1000]=0;
    que.push(p(1000,1000));
    while(que.size()){
        now=que.front();que.pop();
        if(now.first==y&&now.second==x)return visited[now.first][now.second];
        rep(i,MAX_D){
            yy=now.first+dy[i];
            xx=now.second+dx[i];
            if(yy>=0&&yy<=MAX&&xx>=0&&xx<=MAX&&visited[now.first][now.second]+1<visited[yy][xx]){
                que.push(p(yy,xx));
                visited[yy][xx]=visited[now.first][now.second]+1;
            }
        }
    }
    return INFTY;
}

int main(){
    int i,j;
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&i,&j);
        printf("%d\n",bfs(i+1000,j+1000));
    }
    return 0;
}