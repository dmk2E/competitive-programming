/*アルゴリズムと工夫点(Do use hexagon grid/CPU: 10 ms Memory: 4512 KB  Length: 1232 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_X 2000
#define MAX_Y 2000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;

int main(){
    int i,j,ans=0;
    scanf("%d",&n);
    vector<vector<bool> > mmap(MAX_Y+1,vector<bool>(MAX_X+1,false));
    const int PLUS=1000;
    while(n--){
        scanf("%d%d",&i,&j);
        mmap[j+PLUS][i+PLUS]=true;
    }
    const int dy[]={-1,0,-1,1,0,1},dx[]={-1,-1,0,0,1,1},MAX_D=6;
    auto bfs=[&](int y,int x)->void{
        int i;
        P now;
        queue<P> que;
        que.push(P(y,x));
        mmap[y][x]=false;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=now.first+dy[i];
                x=now.second+dx[i];
                if(0<=y&&y<=MAX_Y&&0<=x&&x<=MAX_X&&mmap[y][x]){
                    que.push(P(y,x));
                    mmap[y][x]=false;
                }
            }
        }
    };
    rep(i,MAX_Y+1)rep(j,MAX_X+1){
        if(mmap[i][j]){
            bfs(i,j);
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}