/*アルゴリズムと工夫点(New Friends/CPU: 67 ms Memory: 15944 KB  Length: 949 B)
連結グラフ上では必ず、完全グラフを作成することができるから、連結成分ごとに張れる辺の数を数えて、元々あった辺を引くだけでよい。
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
#define NIL -1
using namespace std;

int n,m;
bool color[MAX_N]={0};
vector<int> adj[MAX_N];

long long bfs(int now){
    int cnt=0;
    queue<int> que;
    cnt++;
    color[now]=true;
    que.push(now);
    while(que.size()){
        now=que.front();que.pop();
        for(int x:adj[now])
            if(color[x]==false){
                que.push(x);
                cnt++;
                color[x]=true;
            }
    }
    return (long long)cnt*(cnt-1)/2;
}

int main(){
    int i,j,k;
    long long cnt=0;
    scanf("%d%d",&n,&m);
    rep(k,m){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    rep(i,n){
        if(color[i]==false){
            cnt+=bfs(i);
        }
    }
    printf("%lld\n",cnt-m);
    return 0;
}